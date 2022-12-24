-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Get related crime report
SELECT * FROM crime_scene_reports WHERE street = "Humphrey Street" AND day = 28;

-- Get related interviews
SELECT * FROM interviews WHERE day = 28 AND month = 7 AND year = 2021 AND transcript LIKE '%bakery%';

-- Get license plates by looking at bakery security logs
SELECT * FROM bakery_security_logs WHERE year = 2021 AND MONTH = 7 AND DAY = 28 AND hour = 10 AND minute <= 15;

-- Get ATM log to get account_number and amount of withdrawn money
SELECT id, account_number, amount FROM atm_transactions WHERE day = 28 AND month = 7 AND year = 2021 AND atm_location = "Leggett Street";

-- Get phone logs
SELECT id, caller, receiver, duration FROM phone_calls WHERE duration < 60 AND day = 28 AND month = 7 AND year = 2021;

-- Get the flight
SELECT * FROM flights WHERE year = 2021 AND month = 7 AND day = 29 ORDER BY hour ASC LIMIT 1;

-- Find the city the thief escaped to
SELECT * FROM airports JOIN flights ON flights.destination_airport_id = airports.id WHERE airports.id = 4;

-- Get list of passangers of the flight
SELECT * FROM passengers  WHERE flight_id = 36;

-- Get of people where thief is
SELECT * FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36);

-- v2 selection of people
SELECT * FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36) AND phone_number IN (SELECT caller FROM phone_calls WHERE duration < 60 AND day = 28 AND month = 7 AND year = 2021);

-- v3 selection of people
SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE day = 28 AND month = 7 AND year = 2021 AND atm_location = "Leggett Street");
-- AFTER SOLVING THE PROBLEM TO CHECK SOLUTION:
-- check50 cs50/problems/2022/x/fiftyville