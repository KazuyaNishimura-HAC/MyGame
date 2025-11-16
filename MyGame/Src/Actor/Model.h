#ifndef MODEL_H_
#define MODEL_H_

class Model
{
public:
    enum Name
    {
        //[Player]
        Player,
        //[Charactor]
        Enemy,
        Boss,
        //[MAP]
        DefaultMap,
        MapCollide,
        //[Object]
        GreatSword,
        //[Debug]
        PathObject,
        EditObject,
        DefaultCharactor
    };
};
#endif
