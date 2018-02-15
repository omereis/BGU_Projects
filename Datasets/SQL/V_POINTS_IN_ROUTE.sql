DROP VIEW IF EXISTS V_POINTS_IN_ROUTE;

CREATE VIEW V_POINTS_IN_ROUTE
(
	ROUTE_ID,
	POINTS
)
AS
SELECT DISTINCT ROUTE_ID,COUNT(POINT_ID) AS 'POINTS' FROM T_POINTS GROUP BY ROUTE_ID;