SELECT
    id, month, day, account_number, amount, atm_location
FROM
    atm_transactions
WHERE
    year = 2020 AND month = 7 AND day = 28 AND 	transaction_type = "withdraw"
ORDER BY
    id;