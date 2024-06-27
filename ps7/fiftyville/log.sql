-- Keep a log of any SQL queries you execute as you solve the mystery.

-- getting a description on the July 28, 2023 attack on Humphrey Street
SELECT description
FROM crime_scene_reports
WHERE year = 2023
AND month = 7
AND day = 28
AND street = 'Humphrey Street';
-- Result:
-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses
-- who were present at the time – each of their interview transcripts mentions the bakery.

-- looking at who left the bakery from 10:15-10:25
SELECT activity
FROM bakery_security_logs
WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 minute <= 25;
-- 8 people exited
-- everyone who exited is a suspect
-- now look at the license plates of these people
SELECT license_plate
FROM bakery_security_logs
WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute <= 25 AND minute >= 15;
-- the 8 people who exited's license plates
-- 5P2BI95       |
-- 94KL13X       |
-- 6P58WS2       |
-- 4328GD8       |
-- G412CB7       |
-- L93JTIZ       |
-- 322W7JE       |
-- 0NTHK55

-- now look at the interviews from this day
SELECT transcript FROM interviews
WHERE year = 2023 AND month = 7 AND day = 28;
-- Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
-- If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
-- I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery,
-- I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
-- As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
-- In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
-- The thief then asked the person on the other end of the phone to purchase the flight ticket

-- Takeaways: his license plate is in the table above
-- He pulled out money at an ATM beforehand
-- Look at call logs from 10:15-10:25
-- Whoever he called and booked the flight ticket is the accomplice
-- Wherever the ticket goes is the city he escaped to

-- looking at who withdrew money today
SELECT account_number FROM atm_transactions
WHERE year = 2023 AND month = 7 AND day = 28
AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw';
-- 28500762       |
-- 28296815       |
-- 76054385       |
-- 49610011       |
-- 16153065       |
-- 25506511       |
-- 81061156       |
-- 26013199

-- getting person_id from these bank account numbers
SELECT person_id FROM bank_accounts WHERE account_number IN (
SELECT account_number FROM atm_transactions
WHERE year = 2023 AND month = 7 AND day = 28
AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw');
-- 686048    |
-- 514354    |
-- 458378    |
-- 395717    |
-- 396669    |
-- 467400    |
-- 449774    |
-- 438727

-- look at people with these ids
SELECT name FROM people WHERE id IN (
SELECT person_id FROM bank_accounts WHERE account_number IN (
SELECT account_number FROM atm_transactions
WHERE year = 2023 AND month = 7 AND day = 28
AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'));
-- Kenny   |
-- Iman    |
-- Benista |
-- Taylor  |
-- Brooke  |
-- Luca    |
-- Diana   |
-- Bruce

-- now look at who has the license plates from earlier
SELECT name FROM people WHERE license_plate IN (
SELECT license_plate
FROM bakery_security_logs
WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute <= 25 AND minute >= 15);
-- Vanessa |
-- Barry   |
-- Iman    |
-- Sofia   |
-- Luca    |
-- Diana   |
-- Kelsey  |
-- Bruce
-- Overlap: Luca, Diana, Bruce => it's one of these three

-- now look at phone calls today and see if any of them called
SELECT caller FROM phone_calls
WHERE year = 2023 AND month = 7 AND day = 28 AND duration < 60;
-- (130) 555-0289 |
-- (499) 555-9472 |
-- (367) 555-5533 |
-- (499) 555-9472 |
-- (286) 555-6063 |
-- (770) 555-1861 |
-- (031) 555-6622 |
-- (826) 555-1652 |
-- (338) 555-6650

-- Now see if this is any of the three's phone number
SELECT name FROM people WHERE phone_number IN (
SELECT caller FROM phone_calls
WHERE year = 2023 AND month = 7 AND day = 28 AND duration < 60);
-- Kenny   |
-- Sofia   |
-- Benista |
-- Taylor  |
-- Diana   |
-- Kelsey  |
-- Bruce   |
-- Carina
-- Takeaways: No Luca, so our 2 suspects are Bruce and Diana

-- Bruce id
SELECT id FROM people WHERE name = 'Bruce' AND phone_number IN (
SELECT caller FROM phone_calls
WHERE year = 2023 AND month = 7 AND day = 28 AND duration < 60);
-- 686048

-- Diana id
SELECT id FROM people WHERE name = 'Diana' AND phone_number IN (
SELECT caller FROM phone_calls
WHERE year = 2023 AND month = 7 AND day = 28 AND duration < 60);
-- 514354

-- look at the earliest flight on July 29, 2023
SELECT id FROM flights
WHERE year = 2023 AND month = 7 AND day = 29
GROUP BY hour ORDER BY COUNT(*) ASC;
--  36 |
-- 43 |
-- 23 |
-- 53 |
-- 18
-- So the flight id is 36

-- look at passengers on flight 36
SELECT passport_number FROM passengers WHERE flight_id = 36;

-- now see if Bruce or Diana has this passport number
SELECT name FROM people WHERE (id = 686048 OR id = 514354) AND passport_number IN (
SELECT passport_number FROM passengers WHERE flight_id = 36);
-- Bruce
-- Bruce is the culprit

-- Now let's see where he's going and who he called
SELECT destination_airport_id FROM flights WHERE id = 36
AND day = 29 AND month = 7 AND year = 2023;
-- 4

SELECT city FROM airports where id = 4;
-- New York City
-- He is flying to New York City

-- Bruce's phone number
SELECT phone_number FROM people where id = 686048;
-- (367) 555-5533

-- who he called
SELECT receiver FROM phone_calls WHERE caller = '(367) 555-5533' AND year = 2023 AND day = 28 AND month = 7 AND duration <= 60;
-- (375) 555-8161

-- get accomplice name from number
SELECT name FROM people WHERE phone_number = '(375) 555-8161';
-- Robin
