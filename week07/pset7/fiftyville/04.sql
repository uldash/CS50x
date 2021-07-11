SELECT
    hour, minute, activity, license_plate
FROM
    courthouse_security_logs
WHERE
    year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 30 AND activity = "exit"
ORDER BY
    minute;