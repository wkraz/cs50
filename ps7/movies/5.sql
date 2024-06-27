SELECT title, year FROM movies WHERE title LIKE "Harry Potter%" GROUP BY year ORDER BY COUNT(*) ASC;
