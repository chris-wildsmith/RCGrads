"""Common types and functions."""


# Classes
# =======

class Direction:
    Fwd = 1
    Rvs = 2


class TurnDirection:
    Cw = 1
    Ccw = 2


class Point(object):
    def __init__(self, x, y):
        self.X = x
        self.Y = y

    def __str__(self):
        return '(' + str(self.X) + ',' + str(self.Y) + ')'

    def __repr__(self):
        return str(self)

    def __eq__(self, other):
        return (self.X == other.X) & (self.Y == other.Y)

    def __ne__(self, other):
        return not self.__eq__(other)


class Waypoint(object):
    def __init__(self, point, direction, speed, size):
        self.Position = point
        self.Direction = direction
        self.Speed = speed
        self.Size = size  # Waypoint is treated as a square, size denotes half the width
        self.Traversed = False

    def __str__(self):
        return '[' + str(self.Position) + ',' + str(self.Direction) + ',' + str(self.Speed) + ',' + str(self.Size) + ']'

    def __repr__(self):
        return str(self)
