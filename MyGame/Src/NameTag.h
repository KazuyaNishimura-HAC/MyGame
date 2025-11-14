#ifndef NAME_TAG_
#define	NAME_TAG_

namespace NameTag {
	struct Scene {
		static constexpr const char* Title = "TitleScene";
		static constexpr const char* Load = "LoadScene";
		static constexpr const char* GamePlay = "GamePlayScene";
		static constexpr const char* Result = "ResultScene";
	};

	struct Priority {
		static constexpr const char* Disable = "Disable";
		static constexpr const char* Player = "Player";
		static constexpr const char* Event = "Event";
		static constexpr const char* Debug = "Debug";
	};

    struct ActorTag {
        static constexpr const char* None = "None";
        static constexpr const char* Charactoe = "Charactor";
        static constexpr const char* Player = "Player";
        static constexpr const char* Enemy = "Enemy";
        static constexpr const char* Object = "Object";
        static constexpr const char* Collide = "Collide";
        static constexpr const char* ATKCollide = "ATKCollide";
    };

	struct ActorName {
		static constexpr const char* None = "None";
		static constexpr const char* Player = "Player";
		static constexpr const char* Enemy = "Enemy";
		static constexpr const char* DefaultEnemy = "DefaultEnemy";
		static constexpr const char* Object = "Object";
		static constexpr const char* PlayerATKCollide = "PlayerATKCollide";
		static constexpr const char* EnemyATKCollide = "EnemyATKCollide";
        static constexpr const char* ParryCollide = "ParryCollide";
	};
	struct PostEffect {
		static constexpr const char* Bloom = "Bloom";
	};
}

//呼び出し簡略化
using SceneName = NameTag::Scene;
using PriorityName = NameTag::Priority;
using ActorTag = NameTag::ActorTag;
using ActorName = NameTag::ActorName;
using EffectName = NameTag::PostEffect;


#endif
