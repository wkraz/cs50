-- (names of people w/ those ids(ids of people also in those movies(id of movies Kevin Bacon is in (id of Kevin Bacon))))
-- find kevin bacon
WITH kevin_bacon AS (
    SELECT id
    FROM people
    WHERE name = 'Kevin Bacon' AND birth = 1958
)

-- Find all movies Kevin Bacon starred in
, kevin_bacon_movies AS (
    SELECT movie_id
    FROM stars
    WHERE person_id = (SELECT id FROM kevin_bacon)
)

-- Find all people who starred in those movies, excluding Kevin Bacon
SELECT DISTINCT p.name
FROM people p
JOIN stars s ON p.id = s.person_id
JOIN kevin_bacon_movies km ON s.movie_id = km.movie_id
WHERE p.id != (SELECT id FROM kevin_bacon)
ORDER BY p.name;
