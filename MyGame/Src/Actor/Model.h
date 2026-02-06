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
        Enemy2,
        Boss,
        //[MAP]
        DefaultMap,
        MapCollide,
        //[Object]
        GreatSword,
        Door,
        //[Debug]
        PathObject,
        EditObject,
        DefaultCharactor
    };
};
#endif
