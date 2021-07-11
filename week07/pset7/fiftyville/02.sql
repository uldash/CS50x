SELECT
    name, transcript
FROM
    interviews
WHERE
    year = 2020 AND month = 7 AND day = 28 AND transcript LIKE "%courthouse%"
ORDER BY
    name;