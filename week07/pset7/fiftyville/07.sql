SELECT
    caller, receiver, duration
FROM
    phone_calls
WHERE
    year = 2020 AND month = 7 AND day = 28 AND duration < 60
ORDER BY
    caller;