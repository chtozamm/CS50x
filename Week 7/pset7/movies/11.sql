-- In 11.sql, write a SQL query to list the titles of the five highest rated movies (in order) that Chadwick Boseman starred in, starting with the highest rated.
SELECT title FROM movies, ratings, stars, people
WHERE people.id = stars.person_id
AND stars.movie_id = movies.id
AND ratings.movie_id = movies.id
AND people.name = "Chadwick Boseman"
ORDER BY ratings.rating DESC
LIMIT 5;