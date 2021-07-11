SELECT
    flight_id, seat, name,	phone_number, people.passport_number, license_plate
FROM
    passengers
JOIN
    people ON passengers.passport_number = people.passport_number
WHERE
    flight_id = 36;