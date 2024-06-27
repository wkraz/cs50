-- find movies with ratings of at least 9.0
WITH highly_rated_movies AS (
    SELECT movie_id
    FROM ratings
    WHERE rating >= 9.0
)

-- see who directed these
, directors_of_highly_rated_movies AS (
    SELECT DISTINCT person_id
    FROM directors
    WHERE movie_id IN (SELECT movie_id FROM highly_rated_movies)
)

-- get the names of these directors
SELECT DISTINCT p.name
FROM people p
JOIN directors_of_highly_rated_movies dhrm ON p.id = dhrm.person_id
ORDER BY p.name;
