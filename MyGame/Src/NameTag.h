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
        static constexpr const char* Collider = "Collider";
        static constexpr const char* ATKCollider = "ATKCollider";
    };

	struct ActorName {
		static constexpr const char* None = "None";
		static constexpr const char* Player = "Player";
		static constexpr const char* Enemy = "Enemy";
		static constexpr const char* SwordEnemy1 = "SwordEnemy1";
        static constexpr const char* Boss = "Boss";
		static constexpr const char* Object = "Object";
		static constexpr const char* PlayerATKCollider = "PlayerATKCollider";
		static constexpr const char* EnemyATKCollider = "EnemyATKCollider";
        static constexpr const char* ParryCollider = "ParryCollider";
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
