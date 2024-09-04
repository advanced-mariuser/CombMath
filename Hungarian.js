/**
 *  @fileoverview
 *  @suppress {deprecated}
 */
goog.provide("ispring.utils.hungarian.HungarianAlgorithmAggregator");

goog.require("ispring.utils.hungarian.Vector");
goog.require("goog.math.Matrix");

goog.scope(() => {
    const Vector = ispring.utils.hungarian.Vector;
    const Matrix = goog.math.Matrix;

    ispring.utils.hungarian.HungarianAlgorithmAggregator = goog.defineClass(null, {
        /**
         * @param {!ispring.utils.hungarian.Vector} oldVertices
         * @param {!ispring.utils.hungarian.Vector} newVertices
         * @param {!Function} costFunc
         */
        constructor: function HungarianAlgorithmAggregator(oldVertices, newVertices, costFunc) {
            this._oldVertices = oldVertices;
            this._newVertices = newVertices;

            // инициализируем и заполняем всю матрицу цен нулями
            const maxDimension = Math.max(oldVertices.size(), newVertices.size());
            this._costsMatrix = new Matrix(new goog.math.Size(maxDimension, maxDimension));

            // заполняем часть или всю матрицу цен, используя функцию подсчета стоимостей
            const thisPtr = this;
            oldVertices.forEach((oldVertex) => {
                newVertices.forEach((newVertex) => {
                    thisPtr._costsMatrix.setValueAt(oldVertex.index(), newVertex.index(), costFunc(oldVertex, newVertex));
                });
            });

            // добавляем границы слева и сверху
            //  * необходимо, чтобы избежать проверок при раскрутке и в общем цикле, когда помечаем переходы
            this._addBorders();
        },

        /**
         * @private
         */
        _addBorders: function () // функция добавляет слева и сверху от матрицы стоимостей - границу заполненную нулями
        {
            const size = this._costsMatrix.getSize().width + 1;

            const rv = [];
            for (let i = 0; i < size; i++) {
                rv[i] = [];
                for (let j = 0; j < size; j++) {
                    rv[i][j] = (i == 0 || j == 0) ? 0 : this._costsMatrix.getValueAt(i - 1, j - 1);
                }
            }
            this._costsMatrix = new Matrix(rv);
        },

        getAlgorithmResult: function () {
            const dimension = this._costsMatrix.getSize().width;

            // потенциалы, содержащие стоимости переходов для строк и колонок, их сумма равна оптимальному решению
            // здесь и далее (dimension, 0) - означает инициализацию вектора размером dimension каждыйц элемент которого по умолчанию равен 0
            const rowPotential = this._initArray(dimension, 0);
            const columnPotential = this._initArray(dimension, 0);

            // массив паросочетаний (строке - соответствует столбец)
            const matchesArray = this._initArray(dimension, 0);

            // ссылки на переходы с минимумами
            const cheapestRows = this._initArray(dimension, 0);

            // цикл по всем столбцам в матрице стоимостей
            for (let column = 1; column < dimension; ++column) {
                // в соотвествие первому элементу берем текущий столбец
                matchesArray[0] = column;

                // обход начинаем с первого элемента строки
                let currentRowElement = 0;

                // минимальная стоимость в определенной строке
                const cheapestCosts = this._initArray(dimension, Number.MAX_VALUE);

                // в строке уже найдено оптимальное решение или нет
                const marked = this._initArray(dimension, false);

                // цикл по элементам массива паросочетаний, пока есть столбцы в соотвествии,
                //  column - помеченный от текущей строки в паросочетании столбец к текущей строке currentRowElement
                for (let column = matchesArray[currentRowElement]; matchesArray[currentRowElement] != 0; column = matchesArray[currentRowElement]) {
                    let currentCheapest = Number.MAX_VALUE;
                    let nextRowElement = 0;

                    // помечаем текущую строку пройденной
                    marked[currentRowElement] = true;


                    // обрабатываем строку #row, обновляя минимумы строк и находя минимальный
                    for (let row = 1; row < dimension; ++row) {
                        if (!marked[row]) {
                            const currentCost = /**@type {number}*/(this._costsMatrix.getValueAt(row, column)) - columnPotential[currentRowElement] - rowPotential[row];
                            if (currentCost < cheapestCosts[row]) {
                                cheapestCosts[row] = currentCost;
                                cheapestRows[row] = currentRowElement;
                            }
                            if (cheapestCosts[row] < currentCheapest) {
                                currentCheapest = cheapestCosts[row];
                                nextRowElement = row;
                            }
                        }
                    }

                    // изменяем потенциалы строк у помеченных, у остальных меняем обновляем минимальные стоимости
                    for (let row = 0; row < dimension; ++row) {
                        if (!marked[row]) {
                            cheapestCosts[row] -= currentCheapest;
                        } else {
                            columnPotential[matchesArray[row]] += currentCheapest;
                            rowPotential[row] -= currentCheapest;
                        }
                    }

                    currentRowElement = nextRowElement;
                }

                // раскручиваем цепь самых "дешевых"
                while (currentRowElement != 0) {
                    const cheapRow = cheapestRows[currentRowElement];
                    matchesArray[currentRowElement] = matchesArray[cheapRow];
                    currentRowElement = cheapRow;
                }
            }

            return this._getFormalizedTransitions(matchesArray);
        },

        /**
         * @param {number} size
         * @param value
         * @private
         */
        _initArray: function (size, value) {
            const array = [];
            for (let i = 0; i < size; i++) {
                array[i] = value;
            }
            return array;
        },

        /**
         * @param {!Array.<number>} transitions
         * @return {!ispring.utils.hungarian.Vector}
         * @private
         */
        _getFormalizedTransitions: function (transitions) // формализуем индексы переходов и помечаем переходы в фиктивные -1
        {
            const ThisClass = ispring.utils.hungarian.HungarianAlgorithmAggregator;
            const formalizedTransitions = new Vector();

            for (let i = 1; i < this._oldVertices.size() + 1; ++i) {
                let transition = transitions[i] - 1;

                if (this._oldVertices.size() > this._newVertices.size()) {
                    for (let fakeIndex = 1; fakeIndex <= this._oldVertices.size() - this._newVertices.size(); fakeIndex++) {
                        if (transition + 1 == fakeIndex + this._newVertices.size()) {
                            transition = ThisClass.USELESS_VERTEX_ID;
                            break;
                        }
                    }
                }
                formalizedTransitions.push(transition);
            }

            // в итоге вектор элементов с переходами, -1 в фиктивные
            return formalizedTransitions;
        },

        statics: {
            USELESS_VERTEX_ID: -1,
        },

    })
});
