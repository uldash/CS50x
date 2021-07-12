SELECT
    atm_transactions.id, year, month, day, atm_transactions.account_number, bank_accounts.person_id, amount, atm_location,
    people.id, people.name, people.phone_number, people.passport_number, people.license_plate
FROM
    atm_transactions
JOIN
    bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
JOIN
    people ON  bank_accounts.person_id = people.id
-- WHERE
--     year = 2020 AND month = 7 AND day = 28 AND 	transaction_type = "withdraw" AND atm_location = "Fifer Street"
WHERE
    year = 2020 AND month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location = "Fifer Street"
ORDER BY
    atm_transactions.id;