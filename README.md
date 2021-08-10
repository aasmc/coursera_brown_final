# Задание по программированию: Транспортный справочник

В этой задаче и последующих её версиях вам нужно реализовать систему хранения транспортных маршрутов и обработки 
запросов к ней. Сначала на вход подаются запросы на создание базы данных, затем — запросы к самой базе.

При проектировании решения учитывайте, что его придётся неоднократно расширять. Авторские решения вы увидите лишь
после успешной сдачи всех версий: таким образом, на протяжении всей череды доработок функционала вы будете иметь 
дело со своей собственной архитектурой кода и почувствуете, какие именно проектировочные решения мешают расширению.

Не пренебрегайте юнит-тестами! Именно они дадут вам уверенность в том, что при изменении части функционала 
не сломается всё остальное.

Как и в других задачах, здесь можно отправить на проверку архив из нескольких файлов.  

## Формат ввода базы данных

В первой строке вводится количество запросов на обновление базы данных, 
затем — по одному на строке — вводятся сами запросы. Запросы бывают двух типов.

### Stop X: latitude, longitude

Остановка с названием X и координатами latitude и longitude.

Гарантируется, что остановка определена не более чем в одном запросе Stop X.

### Bus X: описание маршрута

Запрос на добавление автобуса номер X. Описание маршрута может задаваться в одном из двух форматов (см. пример):
- stop1 - stop2 - ... - stopN: автобус следует от stop1 до stopN и обратно с указанными промежуточными остановками.
- stop1 > stop2 > ... > stopN > stop1: кольцевой маршрут с конечной stop1.

По сути первая версия описания маршрута эквивалентна stop1 > stop2 > ... > stopN-1 > stopN > stopN-1 > ... > stop2 > stop1.

Гарантируется, что каждая из остановок маршрута определена в некотором запросе Stop, а сам маршрут X определён не более
чем в одном запросе Bus.

## Формат запросов к базе данных

В первой строке вводится количество запросов к базе данных, затем — по одному на строке — вводятся сами запросы. 
Запросы бывают (пока что) только одного типа.

### Bus X

Вывести информацию об автобусе X в следующем формате:

Bus X: R forward_stops on route, U unique forward_stops, L route length

- R — количество остановок в маршруте автобуса от stop1 до stop1 включительно.
- U — количество уникальных остановок, на которых останавливается автобус. Одинаковыми считаются остановки, имеющие 
  одинаковые названия.
- L — длина маршрута в метрах. Для простоты будем считать, что автобус проезжает путь между двумя соседними остановками
  по кратчайшему расстоянию по земной поверхности . При вычислении расстояния между двумя точками на земной поверхности 
  считайте число π равным 3.1415926535, а радиус Земли — 6371 км.

Величину расстояния (а также другие вещественные числа в последующих частях задачи) выводите с 6 значащими цифрами, 
то есть предваряя модификатором setprecision(6). (При этом ваши значения сравниваются с верными не посимвольно, а с 
относительной погрешностью 0,0001.)

Если автобус X не найден, выведите Bus X: not found

## Ограничения
- 1 секунда на обработку всех запросов
- Не более 2000 запросов на создание базы.
- Не более 2000 запросов к уже созданной базе.
- Не более 100 остановок в маршруте.
- Не более 25 символов в названии автобуса или остановки. Допустимые символы — латинские буквы, цифры и пробелы.
  Все названия непусты, не могут начинаться на пробелы или заканчиваться ими.

## Пример
### Ввод
```c++
10
Stop Tolstopaltsevo: 55.611087, 37.20829
Stop Marushkino: 55.595884, 37.209755
Bus 256: Biryulyovo Zapadnoye > Biryusinka > Universam > Biryulyovo Tovarnaya > Biryulyovo Passazhirskaya > Biryulyovo Zapadnoye
Bus 750: Tolstopaltsevo - Marushkino - Rasskazovka
Stop Rasskazovka: 55.632761, 37.333324
Stop Biryulyovo Zapadnoye: 55.574371, 37.6517
Stop Biryusinka: 55.581065, 37.64839
Stop Universam: 55.587655, 37.645687
Stop Biryulyovo Tovarnaya: 55.592028, 37.653656
Stop Biryulyovo Passazhirskaya: 55.580999, 37.659164
3
Bus 256
Bus 750
Bus 751
```

### Вывод
```c++
Bus 256: 6 forward_stops on route, 5 unique forward_stops, 4371.02 route length
Bus 750: 5 forward_stops on route, 3 unique forward_stops, 20939.5 route length
Bus 751: not found
```

# Задание по программированию: Транспортный справочник, часть B

Реализуйте предыдущую версию задачи со следующими изменениями.  

## Формат запросов к базе данных: изменения

Stop X (новый запрос)

Вывести информацию об остановке X в следующем формате:

Stop X: buses bus1 bus2 ... busN

- bus1 bus2 ... busN — список автобусов, проходящих через остановку. 
  Дубли не допускаются, названия должны быть отсортированы в алфавитном порядке.
  
- Если остановка X не найдена, выведите Stop X: not found
- Если остановка X существует в базе, но через неё не проходят автобусы, выведите Stop X: no buses

## Пример

### Ввод

```c++
13
Stop Tolstopaltsevo: 55.611087, 37.20829
Stop Marushkino: 55.595884, 37.209755
Bus 256: Biryulyovo Zapadnoye > Biryusinka > Universam > Biryulyovo Tovarnaya > Biryulyovo Passazhirskaya > Biryulyovo Zapadnoye
Bus 750: Tolstopaltsevo - Marushkino - Rasskazovka
Stop Rasskazovka: 55.632761, 37.333324
Stop Biryulyovo Zapadnoye: 55.574371, 37.6517
Stop Biryusinka: 55.581065, 37.64839
Stop Universam: 55.587655, 37.645687
Stop Biryulyovo Tovarnaya: 55.592028, 37.653656
Stop Biryulyovo Passazhirskaya: 55.580999, 37.659164
Bus 828: Biryulyovo Zapadnoye > Universam > Rossoshanskaya ulitsa > Biryulyovo Zapadnoye
Stop Rossoshanskaya ulitsa: 55.595579, 37.605757
Stop Prazhskaya: 55.611678, 37.603831
6
Bus 256
Bus 750
Bus 751
Stop Samara
Stop Prazhskaya
Stop Biryulyovo Zapadnoye
```

### Вывод

```c++
Bus 256: 6 forward_stops on route, 5 unique forward_stops, 4371.02 route length
Bus 750: 5 forward_stops on route, 3 unique forward_stops, 20939.5 route length
Bus 751: not found
Stop Samara: not found
Stop Prazhskaya: no buses
Stop Biryulyovo Zapadnoye: buses 256 828
```
# Задание по программированию: Транспортный справочник, часть C

Реализуйте вторую версию задачи со следующими изменениями.

В базе появляются данные о реальном — измеренном по дорогам — расстоянии между остановками.

Stop X (изменения запроса на добавление остановки)

Новый формат запроса на добавление остановки: Stop X: latitude, longitude, D1m to stop1, D2m to stop2, ...

А именно, теперь после широты и долготы может содержаться список расстояний от этой остановки до соседних.
По умолчанию предполагается, что расстояние от X до stop# равно расстоянию от stop# до X, если только расстояние
от stop# до X не задано явным образом при добавлении остановки stop#

Гарантируется, что каждая из остановок stop# определена в некотором запросе Stop.

В рамках одного запроса Stop все stop# различны, и их количество не превосходит 100.

Все Di являются целыми положительными числами, каждое из которых не превышает 1000000 и не меньше расстояния
по прямой между соответствующими остановками. После каждого расстояния обязательно следует буква m.

Bus X (изменения запроса на информацию об автобусе)

Новый формат ответа на запрос информации об автобусе: Bus X: R forward_stops on route, U unique forward_stops, L route length,
C curvature

- L теперь вычисляется с использованием дорожного расстояния, а не географических координат.
- C (извилистость) — отношение длины маршрута, вычисленной с помощью дорожного расстояния, (новое L) к длине маршрута,
  вычисленной с помощью географического расстояния (L из предыдущих версий задачи). Таким образом,
  C — вещественное число, большее единицы. Оно может быть равно единице только в том случае,
  если автобус едет между остановками по кратчайшему пути (и тогда больше похож на вертолёт), а
  меньше единицы может оказаться только благодаря телепортации или хордовым тоннелям.

Гарантируется, что для любых двух соседних остановок любого маршрута так или иначе задано расстояние по дорогам.

## Пример

### Ввод

```c++
13
Stop Tolstopaltsevo: 55.611087, 37.20829, 3900m to Marushkino
Stop Marushkino: 55.595884, 37.209755, 9900m to Rasskazovka
Bus 256: Biryulyovo Zapadnoye > Biryusinka > Universam > Biryulyovo Tovarnaya > Biryulyovo Passazhirskaya > Biryulyovo Zapadnoye
Bus 750: Tolstopaltsevo - Marushkino - Rasskazovka
Stop Rasskazovka: 55.632761, 37.333324
Stop Biryulyovo Zapadnoye: 55.574371, 37.6517, 7500m to Rossoshanskaya ulitsa, 1800m to Biryusinka, 2400m to Universam
Stop Biryusinka: 55.581065, 37.64839, 750m to Universam
Stop Universam: 55.587655, 37.645687, 5600m to Rossoshanskaya ulitsa, 900m to Biryulyovo Tovarnaya
Stop Biryulyovo Tovarnaya: 55.592028, 37.653656, 1300m to Biryulyovo Passazhirskaya
Stop Biryulyovo Passazhirskaya: 55.580999, 37.659164, 1200m to Biryulyovo Zapadnoye
Bus 828: Biryulyovo Zapadnoye > Universam > Rossoshanskaya ulitsa > Biryulyovo Zapadnoye
Stop Rossoshanskaya ulitsa: 55.595579, 37.605757
Stop Prazhskaya: 55.611678, 37.603831
6
Bus 256
Bus 750
Bus 751
Stop Samara
Stop Prazhskaya
Stop Biryulyovo Zapadnoye
```

### Вывод
```c++
Bus 256: 6 forward_stops on route, 5 unique forward_stops, 5950 route length, 1.361239 curvature
Bus 750: 5 forward_stops on route, 3 unique forward_stops, 27600 route length, 1.318084 curvature
Bus 751: not found
Stop Samara: not found
Stop Prazhskaya: no buses
Stop Biryulyovo Zapadnoye: buses 256 828
```

# Задание по программированию: Транспортный справочник, часть D

В этой версии необходимо перевести весь ввод и вывод на формат JSON. Детали — в примере ниже.

Гарантируется, что вещественные числа не задаются в экспоненциальной записи, то есть обязательно имеют целую часть и,
возможно, дробную часть через десятичную точку.

Каждый запрос к базе дополнительно получает идентификатор в поле id — целое число от 0 до 2147483647. Ответ на запрос 
должен содержать идентификатор этого запроса в поле request_id. Это позволяет выводить ответы на запросы в любом порядке.

Ключи словарей могут располагаться в произвольном порядке. Форматирование (то есть пробельные символы вокруг скобок, 
запятых и двоеточий) не имеет значения как во входном, так и в выходном JSON.

## Пример

### Ввод

```json
{
  "base_requests": [
    {
      "type": "Stop",
      "road_distances": {
        "Marushkino": 3900
      },
      "longitude": 37.20829,
      "name": "Tolstopaltsevo",
      "latitude": 55.611087
    },
    {
      "type": "Stop",
      "road_distances": {
        "Rasskazovka": 9900
      },
      "longitude": 37.209755,
      "name": "Marushkino",
      "latitude": 55.595884
    },
    {
      "type": "Bus",
      "name": "256",
      "forward_stops": [
        "Biryulyovo Zapadnoye",
        "Biryusinka",
        "Universam",
        "Biryulyovo Tovarnaya",
        "Biryulyovo Passazhirskaya",
        "Biryulyovo Zapadnoye"
      ],
      "is_roundtrip": true
    },
    {
      "type": "Bus",
      "name": "750",
      "forward_stops": [
        "Tolstopaltsevo",
        "Marushkino",
        "Rasskazovka"
      ],
      "is_roundtrip": false
    },
    {
      "type": "Stop",
      "road_distances": {},
      "longitude": 37.333324,
      "name": "Rasskazovka",
      "latitude": 55.632761
    },
    {
      "type": "Stop",
      "road_distances": {
        "Rossoshanskaya ulitsa": 7500,
        "Biryusinka": 1800,
        "Universam": 2400
      },
      "longitude": 37.6517,
      "name": "Biryulyovo Zapadnoye",
      "latitude": 55.574371
    },
    {
      "type": "Stop",
      "road_distances": {
        "Universam": 750
      },
      "longitude": 37.64839,
      "name": "Biryusinka",
      "latitude": 55.581065
    },
    {
      "type": "Stop",
      "road_distances": {
        "Rossoshanskaya ulitsa": 5600,
        "Biryulyovo Tovarnaya": 900
      },
      "longitude": 37.645687,
      "name": "Universam",
      "latitude": 55.587655
    },
    {
      "type": "Stop",
      "road_distances": {
        "Biryulyovo Passazhirskaya": 1300
      },
      "longitude": 37.653656,
      "name": "Biryulyovo Tovarnaya",
      "latitude": 55.592028
    },
    {
      "type": "Stop",
      "road_distances": {
        "Biryulyovo Zapadnoye": 1200
      },
      "longitude": 37.659164,
      "name": "Biryulyovo Passazhirskaya",
      "latitude": 55.580999
    },
    {
      "type": "Bus",
      "name": "828",
      "forward_stops": [
        "Biryulyovo Zapadnoye",
        "Universam",
        "Rossoshanskaya ulitsa",
        "Biryulyovo Zapadnoye"
      ],
      "is_roundtrip": true
    },
    {
      "type": "Stop",
      "road_distances": {},
      "longitude": 37.605757,
      "name": "Rossoshanskaya ulitsa",
      "latitude": 55.595579
    },
    {
      "type": "Stop",
      "road_distances": {},
      "longitude": 37.603831,
      "name": "Prazhskaya",
      "latitude": 55.611678
    }
  ],
  "stat_requests": [
    {
      "type": "Bus",
      "name": "256",
      "id": 1965312327
    },
    {
      "type": "Bus",
      "name": "750",
      "id": 519139350
    },
    {
      "type": "Bus",
      "name": "751",
      "id": 194217464
    },
    {
      "type": "Stop",
      "name": "Samara",
      "id": 746888088
    },
    {
      "type": "Stop",
      "name": "Prazhskaya",
      "id": 65100610
    },
    {
      "type": "Stop",
      "name": "Biryulyovo Zapadnoye",
      "id": 1042838872
    }
  ]
}
```

### Вывод

```json
[
  {
    "route_length": 5950,
    "request_id": 1965312327,
    "curvature": 1.36124,
    "stop_count": 6,
    "unique_stop_count": 5
  },
  {
    "route_length": 27600,
    "request_id": 519139350,
    "curvature": 1.31808,
    "stop_count": 5,
    "unique_stop_count": 3
  },
  {
    "request_id": 194217464,
    "error_message": "not found"
  },
  {
    "request_id": 746888088,
    "error_message": "not found"
  },
  {
    "buses": [],
    "request_id": 65100610
  },
  {
    "buses": [
      "256",
      "828"
    ],
    "request_id": 1042838872
  }
]
```

# Задание по программированию: Транспортный справочник, часть E

## Изменения формата ввода

Новая секция — routing_settings

Во входной JSON добавляется ключ "routing_settings", значением которого является словарь с двумя ключами:

- "bus_wait_time" — время ожидания автобуса на остановке (в минутах). Считайте, что когда бы человек ни пришёл на
  остановку и какой бы ни была эта остановка, он будет ждать любой автобус в точности указанное количество минут.
  Значение — целое число от 1 до 1000.

- "bus_velocity" — скорость автобуса (в км/ч). Считайте, что скорость любого автобуса постоянна и в точности равна
  указанному числу. Время стоянки на остановках не учитывается, время разгона и торможения — тоже. Значение —
  вещественное число от 1 до 1000.

### Пример

```json
{
  "routing_settings": {
    "bus_wait_time": 6,
    "bus_velocity": 40
  }
}
```

Данная конфигурация задаёт время ожидания равным 6 минутам и скорость автобусов равной 40 километрам в час.

Новый тип запросов к базе — Route

В список stat_requests добавляются элементы с "type": "Route" — это запросы на построение маршрута между двумя остановками. 
Помимо стандартных свойств "id" и "type", они содержат ещё два:

- "from" — остановка, в которой нужно начать маршрут.

- "to" — остановка, в которой нужно закончить маршрут.

### Пример

```json
{
  "type": "Route",
  "from": "Biryulyovo Zapadnoye",
  "to": "Universam",
  "id": 4
}
```

Данный запрос означает построение маршрута от остановки «Biryulyovo Zapadnoye» до остановки «Universam».

На маршруте человек может использовать несколько автобусов, и даже один автобус несколько раз — 
если на некоторых участках он делает большой крюк и проще срезать на другом автобусе.

Маршрут должен быть наиболее оптимален по времени. Если маршрутов с минимально возможным суммарным временем несколько, 
допускается вывести любой из них: тестирующая система проверяет лишь совпадение времени маршрута с оптимальным и 
корректность самого маршрута.

При прохождении маршрута время расходуется на два типа активностей:

- Ожидание автобуса. Всегда длится bus_wait_time минут.
- Поездка на автобусе. Всегда длится ровно такое количество времени,
  которое требуется для преодоления данного расстояния со скоростью bus_velocity.
  Расстояние между остановками вычисляется по дорогам, то есть с помощью road_distances.

Ходить пешком, выпрыгивать из автобуса между остановками и использовать другие виды транспорта запрещается.
На конечных остановках все автобусы высаживают пассажиров и уезжают в парк. Даже если человек едет на кольцевом
("is_roundtrip": true) маршруте и хочет проехать мимо конечной, он будет вынужден выйти и подождать тот же самый
автобус ровно bus_wait_time минут. Этот и другие случаи разобраны в примерах.

Ответ на запрос Route устроен следующим образом:

```json
{
    "request_id": <id запроса>,
    "total_time": <суммарное время>,
    "items": [
        <элементы маршрута>
    ]
}
```

total_time — суммарное время в минутах, требуемое для прохождения маршрута, выведенное в виде вещественного числа.

Обратите внимание, что расстояние от остановки A до остановки B может быть не равно расстоянию от B до A!

items — список элементов маршрута, каждый из которых описывает непрерывную активность пассажира, требующую временных затрат. А именно, элементы маршрута бывают двух типов.

Wait — подождать нужное количество минут (в нашем случае — всегда bus_wait_time) на указанной остановке:

```json
{
    "type": "Wait",
    "stop_name": "Biryulyovo",
    "time": 6
}
```

Bus — проехать span_count остановок (перегонов между остановками) на автобусе bus, потратив указанное количество минут: 

```json
{
    "type": "Bus",
    "bus": "297",
    "span_count": 2,
    "time": 5.235
}
```

В случае отсутствия маршрута между указанными остановками выведите результат в следующем формате:
```json
{
    "request_id": <id запроса>,
    "error_message": "not found"
}
```

## Реализация

Задача поиска оптимального маршрута данного вида сводится к задаче поиска кратчайшего пути во взвешенном ориентированном графе.

Мы предоставляем вам две небольшие библиотеки.

- graph.h — класс, реализующий взвешенный ориентированный граф.
- router.h — класс, реализующий поиск кратчайшего пути во взвешенном ориентированном графе.

В отличие от парсера JSON в предыдущей версии задачи, эти библиотеки не нуждаются в модификации. 
С другой стороны, вы имеете право не использовать их вовсе или модифицировать произвольным образом.

Моделируя ситуации из реальной жизни разработчиков, обе эти библиотеки предоставляются без документации,
но с самодокументируемым кодом: интерфейсы представленных классов легко читаются по заголовкам публичных методов.

Про эти классы дополнительно известно следующее:

- Вершины и рёбра графа нумеруются автоинкрементно беззнаковыми целыми числами, хранящимися в типах VertexId и EdgeId: 
  вершины нумеруются от 0 до количества вершин минус один в соответствии с пользовательской логикой, а номер очередного 
  ребра выдаётся методом AddEdge, равен нулю для первого вызова метода и при каждом следующем вызове увеличивается на единицу.
  
- Память, необходимая для хранения графа, линейна относительно суммы количеств вершин и рёбер.
- Конструктор и деструктор графа имеют линейную сложность, а остальные методы константны или амортизированно константны.
- Маршрутизатор (класс Router) требует квадратичного относительно количества вершин объёма памяти, не считая памяти, требуемой для хранения кэша маршрутов.
- Конструктор маршрутизатора имеет сложность O(V³+E), где V — количество вершин графа, E — количество рёбер.
- Маршрутизатор не работает с графами, имеющими рёбра отрицательного веса.
- Построение маршрута на готовом маршрутизаторе линейно относительно количества рёбер в маршруте. Таким образом, основная нагрузка построения оптимальных путей ложится на конструктор.

Вам необходимо:

- самостоятельно разобраться с понятиями графов и путями в них;
- придумать, как по транспортному справочнику построить граф, 
  путь наименьшего веса в котором соответствует оптимальному маршруту на автобусах, предварительно определившись, 
  что в этом графе будет являться вершинами, а что — рёбрами;
  
- написать код построения графа и описания маршрута по пути, полученному от маршрутизатора.

## Ограничения

В этой и последующих версиях и количество остановок, и количество автобусов не превышает 100.
Ограничение по времени — 3 секунды на тест, по памяти — 512 МБ

В реальном маршрутизаторе время на предварительную подготовку данных вполне могло бы занимать минуты, что позволило бы увеличить это ограничение.

## Пример 1

### Ввод
```json
{
  "routing_settings": {
    "bus_wait_time": 6,
    "bus_velocity": 40
  },
  "base_requests": [
    {
      "type": "Bus",
      "name": "297",
      "forward_stops": [
        "Biryulyovo Zapadnoye",
        "Biryulyovo Tovarnaya",
        "Universam",
        "Biryulyovo Zapadnoye"
      ],
      "is_roundtrip": true
    },
    {
      "type": "Bus",
      "name": "635",
      "forward_stops": [
        "Biryulyovo Tovarnaya",
        "Universam",
        "Prazhskaya"
      ],
      "is_roundtrip": false
    },
    {
      "type": "Stop",
      "road_distances": {
        "Biryulyovo Tovarnaya": 2600
      },
      "longitude": 37.6517,
      "name": "Biryulyovo Zapadnoye",
      "latitude": 55.574371
    },
    {
      "type": "Stop",
      "road_distances": {
        "Prazhskaya": 4650,
        "Biryulyovo Tovarnaya": 1380,
        "Biryulyovo Zapadnoye": 2500
      },
      "longitude": 37.645687,
      "name": "Universam",
      "latitude": 55.587655
    },
    {
      "type": "Stop",
      "road_distances": {
        "Universam": 890
      },
      "longitude": 37.653656,
      "name": "Biryulyovo Tovarnaya",
      "latitude": 55.592028
    },
    {
      "type": "Stop",
      "road_distances": {},
      "longitude": 37.603938,
      "name": "Prazhskaya",
      "latitude": 55.611717
    }
  ],
  "stat_requests": [
    {
      "type": "Bus",
      "name": "297",
      "id": 1
    },
    {
      "type": "Bus",
      "name": "635",
      "id": 2
    },
    {
      "type": "Stop",
      "name": "Universam",
      "id": 3
    },
    {
      "type": "Route",
      "from": "Biryulyovo Zapadnoye",
      "to": "Universam",
      "id": 4
    },
    {
      "type": "Route",
      "from": "Biryulyovo Zapadnoye",
      "to": "Prazhskaya",
      "id": 5
    }
  ]
}
```

### Вывод

```json
[
    {
        "curvature": 1.42963,
        "unique_stop_count": 3,
        "stop_count": 4,
        "request_id": 1,
        "route_length": 5990
    },
    {
        "curvature": 1.30156,
        "unique_stop_count": 3,
        "stop_count": 5,
        "request_id": 2,
        "route_length": 11570
    },
    {
        "request_id": 3,
        "buses": [
            "297",
            "635"
        ]
    },
    {
        "total_time": 11.235,
        "items": [
            {
                "time": 6,
                "type": "Wait",
                "stop_name": "Biryulyovo Zapadnoye"
            },
            {
                "span_count": 2,
                "bus": "297",
                "type": "Bus",
                "time": 5.235
            }
        ],
        "request_id": 4
    },
    {
        "total_time": 24.21,
        "items": [
            {
                "time": 6,
                "type": "Wait",
                "stop_name": "Biryulyovo Zapadnoye"
            },
            {
                "span_count": 2,
                "bus": "297",
                "type": "Bus",
                "time": 5.235
            },
            {
                "time": 6,
                "type": "Wait",
                "stop_name": "Universam"
            },
            {
                "span_count": 1,
                "bus": "635",
                "type": "Bus",
                "time": 6.975
            }
        ],
        "request_id": 5
    }
]
```

## Пример 2 

### Ввод

```json
{
  "routing_settings": {
    "bus_wait_time": 2,
    "bus_velocity": 30
  },
  "base_requests": [
    {
      "type": "Bus",
      "name": "297",
      "forward_stops": [
        "Biryulyovo Zapadnoye",
        "Biryulyovo Tovarnaya",
        "Universam",
        "Biryusinka",
        "Apteka",
        "Biryulyovo Zapadnoye"
      ],
      "is_roundtrip": true
    },
    {
      "type": "Bus",
      "name": "635",
      "forward_stops": [
        "Biryulyovo Tovarnaya",
        "Universam",
        "Biryusinka",
        "TETs 26",
        "Pokrovskaya",
        "Prazhskaya"
      ],
      "is_roundtrip": false
    },
    {
      "type": "Bus",
      "name": "828",
      "forward_stops": [
        "Biryulyovo Zapadnoye",
        "TETs 26",
        "Biryusinka",
        "Universam",
        "Pokrovskaya",
        "Rossoshanskaya ulitsa"
      ],
      "is_roundtrip": false
    },
    {
      "type": "Stop",
      "road_distances": {
        "Biryulyovo Tovarnaya": 2600,
        "TETs 26": 1100
      },
      "longitude": 37.6517,
      "name": "Biryulyovo Zapadnoye",
      "latitude": 55.574371
    },
    {
      "type": "Stop",
      "road_distances": {
        "Biryusinka": 760,
        "Biryulyovo Tovarnaya": 1380,
        "Pokrovskaya": 2460
      },
      "longitude": 37.645687,
      "name": "Universam",
      "latitude": 55.587655
    },
    {
      "type": "Stop",
      "road_distances": {
        "Universam": 890
      },
      "longitude": 37.653656,
      "name": "Biryulyovo Tovarnaya",
      "latitude": 55.592028
    },
    {
      "type": "Stop",
      "road_distances": {
        "Apteka": 210,
        "TETs 26": 400
      },
      "longitude": 37.64839,
      "name": "Biryusinka",
      "latitude": 55.581065
    },
    {
      "type": "Stop",
      "road_distances": {
        "Biryulyovo Zapadnoye": 1420
      },
      "longitude": 37.652296,
      "name": "Apteka",
      "latitude": 55.580023
    },
    {
      "type": "Stop",
      "road_distances": {
        "Pokrovskaya": 2850
      },
      "longitude": 37.642258,
      "name": "TETs 26",
      "latitude": 55.580685
    },
    {
      "type": "Stop",
      "road_distances": {
        "Rossoshanskaya ulitsa": 3140
      },
      "longitude": 37.635517,
      "name": "Pokrovskaya",
      "latitude": 55.603601
    },
    {
      "type": "Stop",
      "road_distances": {
        "Pokrovskaya": 3210
      },
      "longitude": 37.605757,
      "name": "Rossoshanskaya ulitsa",
      "latitude": 55.595579
    },
    {
      "type": "Stop",
      "road_distances": {
        "Pokrovskaya": 2260
      },
      "longitude": 37.603938,
      "name": "Prazhskaya",
      "latitude": 55.611717
    },
    {
      "type": "Bus",
      "name": "750",
      "forward_stops": [
        "Tolstopaltsevo",
        "Rasskazovka"
      ],
      "is_roundtrip": false
    },
    {
      "type": "Stop",
      "road_distances": {
        "Rasskazovka": 13800
      },
      "longitude": 37.20829,
      "name": "Tolstopaltsevo",
      "latitude": 55.611087
    },
    {
      "type": "Stop",
      "road_distances": {},
      "longitude": 37.333324,
      "name": "Rasskazovka",
      "latitude": 55.632761
    }
  ],
  "stat_requests": [
    {
      "type": "Bus",
      "name": "297",
      "id": 1
    },
    {
      "type": "Bus",
      "name": "635",
      "id": 2
    },
    {
      "type": "Bus",
      "name": "828",
      "id": 3
    },
    {
      "type": "Stop",
      "name": "Universam",
      "id": 4
    },
    {
      "type": "Route",
      "from": "Biryulyovo Zapadnoye",
      "to": "Apteka",
      "id": 5
    },
    {
      "type": "Route",
      "from": "Biryulyovo Zapadnoye",
      "to": "Pokrovskaya",
      "id": 6
    },
    {
      "type": "Route",
      "from": "Biryulyovo Tovarnaya",
      "to": "Pokrovskaya",
      "id": 7
    },
    {
      "type": "Route",
      "from": "Biryulyovo Tovarnaya",
      "to": "Biryulyovo Zapadnoye",
      "id": 8
    },
    {
      "type": "Route",
      "from": "Biryulyovo Tovarnaya",
      "to": "Prazhskaya",
      "id": 9
    },
    {
      "type": "Route",
      "from": "Apteka",
      "to": "Biryulyovo Tovarnaya",
      "id": 10
    },
    {
      "type": "Route",
      "from": "Biryulyovo Zapadnoye",
      "to": "Tolstopaltsevo",
      "id": 11
    }
  ]
}
```

### Вывод

```json
[
    {
        "stop_count": 6,
        "route_length": 5880,
        "unique_stop_count": 5,
        "curvature": 1.36159,
        "request_id": 1
    },
    {
        "stop_count": 11,
        "route_length": 14810,
        "unique_stop_count": 6,
        "curvature": 1.12195,
        "request_id": 2
    },
    {
        "stop_count": 11,
        "route_length": 15790,
        "unique_stop_count": 6,
        "curvature": 1.31245,
        "request_id": 3
    },
    {
        "buses": [
            "297",
            "635",
            "828"
        ],
        "request_id": 4
    },
    {
        "items": [
            {
                "time": 2,
                "stop_name": "Biryulyovo Zapadnoye",
                "type": "Wait"
            },
            {
                "time": 3,
                "bus": "828",
                "span_count": 2,
                "type": "Bus"
            },
            {
                "time": 2,
                "stop_name": "Biryusinka",
                "type": "Wait"
            },
            {
                "time": 0.42,
                "bus": "297",
                "span_count": 1,
                "type": "Bus"
            }
        ],
        "request_id": 5,
        "total_time": 7.42
    },
    {
        "items": [
            {
                "time": 2,
                "stop_name": "Biryulyovo Zapadnoye",
                "type": "Wait"
            },
            {
                "time": 9.44,
                "bus": "828",
                "span_count": 4,
                "type": "Bus"
            }
        ],
        "request_id": 6,
        "total_time": 11.44
    },
    {
        "items": [
            {
                "time": 2,
                "stop_name": "Biryulyovo Tovarnaya",
                "type": "Wait"
            },
            {
                "time": 1.78,
                "bus": "635",
                "span_count": 1,
                "type": "Bus"
            },
            {
                "time": 2,
                "stop_name": "Universam",
                "type": "Wait"
            },
            {
                "time": 4.92,
                "bus": "828",
                "span_count": 1,
                "type": "Bus"
            }
        ],
        "request_id": 7,
        "total_time": 10.7
    },
    {
        "items": [
            {
                "time": 2,
                "stop_name": "Biryulyovo Tovarnaya",
                "type": "Wait"
            },
            {
                "time": 6.56,
                "bus": "297",
                "span_count": 4,
                "type": "Bus"
            }
        ],
        "request_id": 8,
        "total_time": 8.56
    },
    {
        "items": [
            {
                "time": 2,
                "stop_name": "Biryulyovo Tovarnaya",
                "type": "Wait"
            },
            {
                "time": 14.32,
                "bus": "635",
                "span_count": 5,
                "type": "Bus"
            }
        ],
        "request_id": 9,
        "total_time": 16.32
    },
    {
        "items": [
            {
                "time": 2,
                "stop_name": "Apteka",
                "type": "Wait"
            },
            {
                "time": 2.84,
                "bus": "297",
                "span_count": 1,
                "type": "Bus"
            },
            {
                "time": 2,
                "stop_name": "Biryulyovo Zapadnoye",
                "type": "Wait"
            },
            {
                "time": 5.2,
                "bus": "297",
                "span_count": 1,
                "type": "Bus"
            }
        ],
        "request_id": 10,
        "total_time": 12.04
    },
    {
        "error_message": "not found",
        "request_id": 11
    }
]
```

## Пример 3

### Ввод

```json
{
  "routing_settings": {
    "bus_wait_time": 2,
    "bus_velocity": 30
  },
  "base_requests": [
    {
      "type": "Bus",
      "name": "289",
      "forward_stops": [
        "Zagorye",
        "Lipetskaya ulitsa 46",
        "Lipetskaya ulitsa 40",
        "Lipetskaya ulitsa 40",
        "Lipetskaya ulitsa 46",
        "Moskvorechye",
        "Zagorye"
      ],
      "is_roundtrip": true
    },
    {
      "type": "Stop",
      "road_distances": {
        "Lipetskaya ulitsa 46": 230
      },
      "longitude": 37.68372,
      "name": "Zagorye",
      "latitude": 55.579909
    },
    {
      "type": "Stop",
      "road_distances": {
        "Lipetskaya ulitsa 40": 390,
        "Moskvorechye": 12400
      },
      "longitude": 37.682205,
      "name": "Lipetskaya ulitsa 46",
      "latitude": 55.581441
    },
    {
      "type": "Stop",
      "road_distances": {
        "Lipetskaya ulitsa 40": 1090,
        "Lipetskaya ulitsa 46": 380
      },
      "longitude": 37.679133,
      "name": "Lipetskaya ulitsa 40",
      "latitude": 55.584496
    },
    {
      "type": "Stop",
      "road_distances": {
        "Zagorye": 10000
      },
      "longitude": 37.638433,
      "name": "Moskvorechye",
      "latitude": 55.638433
    }
  ],
  "stat_requests": [
    {
      "type": "Bus",
      "name": "289",
      "id": 1
    },
    {
      "type": "Route",
      "from": "Zagorye",
      "to": "Moskvorechye",
      "id": 2
    },
    {
      "type": "Route",
      "from": "Moskvorechye",
      "to": "Zagorye",
      "id": 3
    },
    {
      "type": "Route",
      "from": "Lipetskaya ulitsa 40",
      "to": "Lipetskaya ulitsa 40",
      "id": 4
    }
  ]
}
```

### Вывод

```json
[
    {
        "unique_stop_count": 4,
        "stop_count": 7,
        "request_id": 1,
        "curvature": 1.63414,
        "route_length": 24490
    },
    {
        "total_time": 29.26,
        "items": [
            {
                "time": 2,
                "stop_name": "Zagorye",
                "type": "Wait"
            },
            {
                "time": 0.46,
                "bus": "289",
                "span_count": 1,
                "type": "Bus"
            },
            {
                "time": 2,
                "stop_name": "Lipetskaya ulitsa 46",
                "type": "Wait"
            },
            {
                "time": 24.8,
                "bus": "289",
                "span_count": 1,
                "type": "Bus"
            }
        ],
        "request_id": 2
    },
    {
        "total_time": 22,
        "items": [
            {
                "time": 2,
                "stop_name": "Moskvorechye",
                "type": "Wait"
            },
            {
                "time": 20,
                "bus": "289",
                "span_count": 1,
                "type": "Bus"
            }
        ],
        "request_id": 3
    },
    {
        "total_time": 0,
        "items": [],
        "request_id": 4
    }
]
```

