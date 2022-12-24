-- 1st SOLUTION ----------------------------------------

-- SELECT title FROM movies
-- WHERE id IN (SELECT movie_id FROM stars WHERE person_id = (SELECT id FROM people WHERE name = "Johnny Depp"))
-- INTERSECT
-- SELECT title FROM movies
-- WHERE id IN (SELECT movie_id FROM stars WHERE person_id = (SELECT id FROM people WHERE name = "Helena Bonham Carter"));

-- 2nd SOLUTION ----------------------------------------

SELECT movies.title FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
WHERE people.name = "Johnny Depp" AND movies.title IN(
    SELECT movies.title FROM people
    JOIN stars ON people.id = stars.person_id
    JOIN movies ON stars.movie_id = movies.id
    WHERE people.name = "Helena Bonham Carter"
);