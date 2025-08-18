#ifndef MODEL_H_
#define MODEL_H_

class Model
{
public:
    enum Name
    {
        //[Player]
        Player,
        //[MAP]
        StraightRoad,
        HoleRoad,
        LeftCurvingRoad,
        LeftCurvingRoad2,
        LeftCurvingRoad3,
        LeftCurvingRoad4,
        RightCurvingRoad,
        RightCurvingRoad2,
        RightCurvingRoad3,
        RightCurvingRoad4,
        LeftStraightRoad,
        MiddleStraightRoad,
        SharpLeftCurvingRoad,
        SharpRightCurvingRoad,
        //[Debug]
        PathObject,
        EditObject,
        
        //[Item]
        RandomBox,
        FlipIcon,
        MagicHand,

        //[Gimmick]
        GoalObject,
        AccelerationFloor,
        AccelerationRing,
        VerticalLaser,
        HorizontalLaser,
        Guardrail,
        ColliderGuardrail,
        Sign
    };
};
#endif
