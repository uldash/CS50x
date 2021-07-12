-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT
    description
FROM
    crime_scene_reports
WHERE
    street = "Chamberlin Street" AND year = 2020 AND month = 7 AND day = 28;
--
SELECT
    name, transcript
FROM
    interviews
WHERE
    year = 2020 AND month = 7 AND day = 28 AND transcript LIKE "%courthouse%"
ORDER BY
    name;
--
SELECT
    atm_transactions.id, year, month, day, atm_transactions.account_number, bank_accounts.person_id, amount, atm_location,
    people.id, people.name, people.phone_number, people.passport_number, people.license_plate
FROM
    atm_transactions
JOIN
    bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
JOIN
    people ON  bank_accounts.person_id = people.id
WHERE
    year = 2020 AND month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location = "Fifer Street"
ORDER BY
    atm_transactions.id;
--
SELECT
    hour, minute, activity, license_plate
FROM
    courthouse_security_logs
WHERE
    year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 30 AND activity = "exit"
ORDER BY
    minute;
--
SELECT
    flights.id, destination_airport_id
FROM
    flights
JOIN
    airports ON flights.origin_airport_id = airports.id
WHERE
    year = 2020 AND month = 7 AND day = 29 AND city = "Fiftyville"
ORDER BY
    hour
LIMIT
    1;
--
SELECT
    flight_id, seat, name,	phone_number, people.passport_number, license_plate
FROM
    passengers
JOIN
    people ON passengers.passport_number = people.passport_number
WHERE
    flight_id = 36;
--
SELECT
    caller, receiver, duration
FROM
    phone_calls
WHERE
    year = 2020 AND month = 7 AND day = 28 AND duration < 60
ORDER BY
    caller;
--
SELECT
    *
FROM
    people
WHERE
    phone_number = "(375) 555-8161";

-- Преступление 20200728, город Fiftyville
-- Кража утки CS50 произошла в 10:15 в здании суда на улице Чемберлин. Сегодня были проведены интервью с тремя свидетелями, которые присутствовали в то время, и в каждой из стенограмм их интервью упоминается здание суда.

-- Свидетели
-- Eugene
-- Я не знаю имени вора, но это был кто-то, кого я узнал. Ранее этим утром, прежде чем я прибыл в здание суда, я проходил мимо банкомата на Файфер-стрит и увидел, что вор снимает деньги.
-- Raymond
-- Когда вор выходил из здания суда, он позвонил кому-то, кто разговаривал с ними меньше минуты. Во время разговора я слышал, как вор сказал, что завтра они планируют вылететь из Файфтивилля самым ранним рейсом. Затем вор попросил человека на другом конце телефона купить билет на самолет.
-- Ruth
-- Где-то через десять минут после кражи я увидел, как вор сел в машину на стоянке у здания суда и уехал. Если у вас есть кадры с камер видеонаблюдения со стоянки у здания суда, вы можете поискать машины, которые покинули стоянку в этот период времени.

-- 1.	Вор снимал деньги в банкомате у здания суда до 10:15 – Номер счета? На кого открыт?
-- id | year | month | day | account_number | person_id | amount | atm_location | id | name | phone_number | passport_number | license_plate
-- 246 | 2020 | 7 | 28 | 28500762 | 467400 | 48 | Fifer Street | 467400 | Danielle | (389) 555-5198 | 8496433585 | 4328GD8
-- 264 | 2020 | 7 | 28 | 28296815 | 395717 | 20 | Fifer Street | 395717 | Bobby | (826) 555-1652 | 9878712108 | 30G67EN
-- 266 | 2020 | 7 | 28 | 76054385 | 449774 | 60 | Fifer Street | 449774 | Madison | (286) 555-6063 | 1988161715 | 1106N58
-- 267 | 2020 | 7 | 28 | 49610011 | 686048 | 50 | Fifer Street | 686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X
-- 269 | 2020 | 7 | 28 | 16153065 | 458378 | 80 | Fifer Street | 458378 | Roy | (122) 555-4581 | 4408372428 | QX4YZN3
-- 288 | 2020 | 7 | 28 | 25506511 | 396669 | 20 | Fifer Street | 396669 | Elizabeth | (829) 555-5269 | 7049073643 | L93JTIZ
-- 313 | 2020 | 7 | 28 | 81061156 | 438727 | 30 | Fifer Street | 438727 | Victoria | (338) 555-6650 | 9586786673 | 8X428L0
-- 336 | 2020 | 7 | 28 | 26013199 | 514354 | 35 | Fifer Street | 514354 | Russell | (770) 555-1861 | 3592750733 | 322W7JE
-- 2.	Вор позвонил кому-то и разговаривал меньше минуты после 10:15 – С кем говорил? Какой самый ранний рейс 2020 07 29? Список пассажиров рейса (там будет вор)?
-- Сообщник купит билеты на рейс.
-- Самый первый рейс 29-го:
-- В Лондон, в 8.20, рейс 36
-- Список Пассажиров рейса 36:
-- flight_id | seat | name | phone_number | passport_number | license_plate
-- 36 | 2A | Doris | (066) 555-9701 | 7214083635 | M51FA04
-- 36 | 3B | Roger | (130) 555-0289 | 1695452385 | G412CB7
-- 36 | 4A | Ernest | (367) 555-5533 | 5773159633 | 94KL13X
-- 36 | 5C | Edward | (328) 555-1152 | 1540955065 | 130LD9Z
-- 36 | 6C | Evelyn | (499) 555-9472 | 8294398571 | 0NTHK55
-- 36 | 6D | Madison | (286) 555-6063 | 1988161715 | 1106N58
-- 36 | 7A | Bobby | (826) 555-1652 | 9878712108 | 30G67EN
-- 36 | 7B | Danielle | (389) 555-5198 | 8496433585 | 4328GD8
-- 3.	Примерно в 10:25 от здания суда отъехала машина вора, можно узнать номер машины.
-- hour | minute | activity | license_plate
-- 10 | 16 | exit | 5P2BI95
-- 10 | 18 | exit | 94KL13X
-- 10 | 18 | exit | 6P58WS2
-- 10 | 19 | exit | 4328GD8
-- 10 | 20 | exit | G412CB7
-- 10 | 21 | exit | L93JTIZ
-- 10 | 23 | exit | 322W7JE
-- 10 | 23 | exit | 0NTHK55

-- 4.	Совпадающие номера машин из списка пассажиров рейса 36 и списка отъехавших со стоянки от здания суда:
-- M51FA04	5P2BI95
-- G412CB7	94KL13X
-- 94KL13X	6P58WS2
-- 130LD9Z	4328GD8
-- 0NTHK55	G412CB7
-- 1106N58	L93JTIZ
-- 30G67EN	322W7JE
-- 4328GD8	0NTHK55
-- 5.	Вор подозреваемые:
-- flight_id | seat | name | phone_number | passport_number | license_plate
-- 36 | 3B | Roger | (130) 555-0289 | 1695452385 | G412CB7
-- 36 | 4A | Ernest | (367) 555-5533 | 5773159633 | 94KL13X
-- 36 | 6C | Evelyn | (499) 555-9472 | 8294398571 | 0NTHK55
-- 36 | 7B | Danielle | (389) 555-5198 | 8496433585 | 4328GD8
-- 6.	Список звонков от здания суда
-- caller | receiver | duration
-- (031) 555-6622 | (910) 555-3251 | 38
-- (130) 555-0289 | (996) 555-8899 | 51
-- (286) 555-6063 | (676) 555-6554 | 43
-- (338) 555-6650 | (704) 555-2131 | 54
-- (367) 555-5533 | (375) 555-8161 | 45
-- (499) 555-9472 | (892) 555-8872 | 36
-- (499) 555-9472 | (717) 555-1342 | 50
-- (770) 555-1861 | (725) 555-3243 | 49
-- (826) 555-1652 | (066) 555-9701 | 55
-- 7.	Вор подозреваемые:
-- flight_id | seat | name | phone_number | passport_number | license_plate
-- 36 | 3B | Roger | (130) 555-0289 | 1695452385 | G412CB7
-- 36 | 4A | Ernest | (367) 555-5533 | 5773159633 | 94KL13X
-- 8.	Вор, сравним с записью из банкомата, останется: Ernest
-- 267 | 2020 | 7 | 28 | 49610011 | 686048 | 50 | Fifer Street | 686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X

-- 9.	Ernest звонил на номер
-- (367) 555-5533 | (375) 555-8161 | 45
-- 10.	По базе people: Berthold
-- id | name | phone_number | passport_number | license_plate
-- 864400 | Berthold | (375) 555-8161 |  | 4V16VO0