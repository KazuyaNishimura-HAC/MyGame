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

	struct Actor {
		static constexpr const char* None = "None";
		static constexpr const char* Player = "Player";
		static constexpr const char* Enemy = "Enemy";
		static constexpr const char* Object = "Object";
	};
	struct PostEffect {
		static constexpr const char* Bloom = "Bloom";
	};
}

//åƒÇ—èoÇµä»ó™âª
using SceneName = NameTag::Scene;
using PriorityName = NameTag::Priority;
using ActorName = NameTag::Actor;
using EffectName = NameTag::PostEffect;


#endif