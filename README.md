Программа, реализующая выгрузка страниц по алгоритму NFU (редко используемая страница). Для такой реализации необходим программный счетчик размером n бит, связанный с каждой страницей памяти и изначально равный нулю.
Во время каждого прерывания по таймеру, ОС производит побитовый сдвиг вправо каждого счетчика на один бит, а значением самого старшего (n-1)-го бита (крайнего слева) становится значение бита R (бита обращения) страницы. Понятно, что страница, к которой не обращались в течение 4-х тиков таймера, будет иметь в старших разрядах 4 нулевых бита, а ее счетчик будет иметь меньшее значение, чем у страницы, к которой не обращались в течение трех тиков.

В программе присутствуют два глобальных байтовых массива, один из которых олицетворяет оперативную память, а другой – внешний носитель. Размер каждого из массивов должен быть не менее чем 1024 байта. Использование других глобальных переменных в программе запрещено (то есть вся информация о местоположении страницы памяти и других ее характеристиках должна находиться в массиве «оперативной памяти»). 
Программа реализовывает сквозную адресацию ячеек «виртуальной памяти» (байт).
Пример отображения информации о блоке:
1 - 0 - 00000000 - адрес: 32
где: 1 - номер ячейки, 0 - специальный бит, хатактеризующий "обращение" к странице (1 - последнее обращение было именно к этой странице, 0 - к странице не обращались), 00000000 - счетчик, который реализует побитовое смещение обращений к ячейке памяти.
В случае, когда требуется ячейка памяти, которая находится на внешем носителе, алгоритм свопинга меняет редко используемую страницу из оперативной памяти со страницой, которая в данный момент необходима. У страницы, оказавшейся в ВЗУ обнуляется счетчик, а странице, которую вызвали из ВЗУ - выставляется бит обращения.
