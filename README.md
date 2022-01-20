# Goertzel_Filter
Реализация алгоритма Герцеля ДПФ на контроллерах Arduino

Алгоритм Гёрцеля (Goertzel algorithm) — это специальная реализация дискретного преобразования Фурье (ДПФ) в форме рекурсивного фильтра. 
В отличие от быстрого преобразования Фурье, вычисляющего все частотные компоненты ДПФ, алгоритм Гёрцеля позволяет эффективно вычислить значение одного частотного компонента.
Библиотека может быть использованая для создания низкочастотных цифровых филитров с относительно узкой полосой пропускания.
Также возможно применение библиотеки для выделения и последующей обработки промежуточной частоты в самодельной измерительной аппаратуре.
## Совместимость
В библиотеке используются стандартные фунции языка Arduino, поэтому библиотека теоретически должна работать на всех контроллерах Arduino.
Экспериментально проверена на Arduino UNO, Arduino Nano и Arduino DUE
