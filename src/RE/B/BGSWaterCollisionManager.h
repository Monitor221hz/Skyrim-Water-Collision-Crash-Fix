#pragma once
#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkpShape.h"
#include <cstdint>

namespace RE
{
	class bhkRigidBody;
	class bhkWorld;
	class TESWaterForm;

	class hkpPhantomCallbackShape : public hkpShape
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkpPhantomCallbackShape;
		inline static constexpr auto VTABLE = VTABLE_hkpPhantomCallbackShape;
	};
	static_assert(sizeof(hkpPhantomCallbackShape) == 0x20);

	namespace BGSWaterCollisionManager
	{

		template <class T>
		struct BSScrapArray
		{
			T *data;				// 00
			void *allocator;		// 08
			std::uint32_t size;		// 10
			std::uint32_t capacity; // 14
		};
		static_assert(sizeof(BSScrapArray<void *>) == 0x18);

		class BGSWaterUpdateI
		{
		public:
			enum Flag : std::uint32_t
			{
				kNone = 0,
				kInert = 1 << 0,
			};

			// members
			void *vftable;						// 00
			std::uint32_t flags;				// 08
			std::uint32_t pad0C;				// 0C
			BSScrapArray<void *> trackedBodies; // 10
			BGSWaterUpdateI *next;				// 28
			TESWaterForm *waterType;			// 30
			void *context;						// 38
			bhkRigidBody *body;					// 40
		};
		static_assert(sizeof(BGSWaterUpdateI) == 0x48);

		class bhkPlaceableWater : public hkpPhantomCallbackShape // 00
		{
		public:
			inline static constexpr auto RTTI = RTTI_BGSWaterCollisionManager__bhkPlaceableWater;
			inline static constexpr auto VTABLE = VTABLE_BGSWaterCollisionManager__bhkPlaceableWater;

			BGSWaterUpdateI updateI;  // 20
			std::uint32_t usageCount; // 68
			std::uint32_t pad6C;	  // 6C
		};
		static_assert(sizeof(bhkPlaceableWater) == 0x70);

		struct bhkAutoWater
		{
			void *vftable;			  // 00
			std::uint32_t pad08;	  // 08
			std::uint32_t pad0C;	  // 0C
			void *havokObject;		  // 10
			std::uint8_t pad18[0x10]; // 18
			std::uint8_t unk28;		  // 28
			std::uint8_t pad29[7];	  // 29
		};
		static_assert(sizeof(bhkAutoWater) == 0x30);
	};
}
