-- SELECT
--     city
-- FROM
--     airports
-- WHERE
--     id =
-- (SELECT
--     destination_airport_id
-- FROM
--     flights
-- JOIN
--     airports ON flights.origin_airport_id = airports.id
-- WHERE
--     year = 2020 AND month = 7 AND day = 29 AND  city = "Fiftyville"
-- ORDER BY
--     hour
-- LIMIT 1);
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