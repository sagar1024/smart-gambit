#ifndef MOVE_H
#define MOVE_H

class Move
{
public:
    int from;
    int to;

    // Constructor
    Move(int fromSquare, int toSquare) : from(fromSquare), to(toSquare) {}

    // Default constructor
    Move() : from(-1), to(-1) {}

    // Comparison operator for equality (optional)
    bool operator==(const Move &other) const
    {
        return (from == other.from && to == other.to);
    }
};

#endif // MOVE_H
