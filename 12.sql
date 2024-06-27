-- identify bradley cooper and jennifer lawrence
WITH bradley_cooper AS (
    SELECT id
    FROM people
    WHERE name = 'Bradley Cooper'
),
jennifer_lawrence AS (
    SELECT id
    FROM people
    WHERE name = 'Jennifer Lawrence'
)

-- find movies they starred in
, bradley_cooper_movies AS (
    SELECT movie_id
    FROM stars
    WHERE person_id = (SELECT id FROM bradley_cooper)
)

, jennifer_lawrence_movies AS (
    SELECT movie_id
    FROM stars
    WHERE person_id = (SELECT id FROM jennifer_lawrence)
)

-- find what movies they have in common
SELECT m.title
FROM movies m
WHERE m.id IN (
    SELECT movie_id
    FROM bradley_cooper_movies
    INTERSECT
    SELECT movie_id
    FROM jennifer_lawrence_movies
);
