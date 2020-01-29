// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FPSGame/Public/FPSBombActor.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFPSBombActor() {}
// Cross Module References
	FPSGAME_API UClass* Z_Construct_UClass_AFPSBombActor_NoRegister();
	FPSGAME_API UClass* Z_Construct_UClass_AFPSBombActor();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_FPSGame();
	ENGINE_API UClass* Z_Construct_UClass_URadialForceComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UBoxComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UParticleSystem_NoRegister();
// End Cross Module References
	void AFPSBombActor::StaticRegisterNativesAFPSBombActor()
	{
	}
	UClass* Z_Construct_UClass_AFPSBombActor_NoRegister()
	{
		return AFPSBombActor::StaticClass();
	}
	struct Z_Construct_UClass_AFPSBombActor_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RadialForceComp_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_RadialForceComp;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_BombBox_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_BombBox;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_BombMesh_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_BombMesh;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ExplosionTemplate_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ExplosionTemplate;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ExplodeDelay_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_ExplodeDelay;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AFPSBombActor_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_FPSGame,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFPSBombActor_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "FPSBombActor.h" },
		{ "ModuleRelativePath", "Public/FPSBombActor.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFPSBombActor_Statics::NewProp_RadialForceComp_MetaData[] = {
		{ "Category", "Components" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/FPSBombActor.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AFPSBombActor_Statics::NewProp_RadialForceComp = { "RadialForceComp", nullptr, (EPropertyFlags)0x00100000000a0009, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AFPSBombActor, RadialForceComp), Z_Construct_UClass_URadialForceComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AFPSBombActor_Statics::NewProp_RadialForceComp_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AFPSBombActor_Statics::NewProp_RadialForceComp_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFPSBombActor_Statics::NewProp_BombBox_MetaData[] = {
		{ "Category", "bomb box" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/FPSBombActor.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AFPSBombActor_Statics::NewProp_BombBox = { "BombBox", nullptr, (EPropertyFlags)0x00100000000a0009, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AFPSBombActor, BombBox), Z_Construct_UClass_UBoxComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AFPSBombActor_Statics::NewProp_BombBox_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AFPSBombActor_Statics::NewProp_BombBox_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFPSBombActor_Statics::NewProp_BombMesh_MetaData[] = {
		{ "Category", "bomb mesh" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/FPSBombActor.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AFPSBombActor_Statics::NewProp_BombMesh = { "BombMesh", nullptr, (EPropertyFlags)0x0010000000090009, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AFPSBombActor, BombMesh), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AFPSBombActor_Statics::NewProp_BombMesh_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AFPSBombActor_Statics::NewProp_BombMesh_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFPSBombActor_Statics::NewProp_ExplosionTemplate_MetaData[] = {
		{ "Category", "explosion template" },
		{ "ModuleRelativePath", "Public/FPSBombActor.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AFPSBombActor_Statics::NewProp_ExplosionTemplate = { "ExplosionTemplate", nullptr, (EPropertyFlags)0x0010000000010001, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AFPSBombActor, ExplosionTemplate), Z_Construct_UClass_UParticleSystem_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AFPSBombActor_Statics::NewProp_ExplosionTemplate_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AFPSBombActor_Statics::NewProp_ExplosionTemplate_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFPSBombActor_Statics::NewProp_ExplodeDelay_MetaData[] = {
		{ "Category", "explode delay" },
		{ "ModuleRelativePath", "Public/FPSBombActor.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AFPSBombActor_Statics::NewProp_ExplodeDelay = { "ExplodeDelay", nullptr, (EPropertyFlags)0x0010000000010001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AFPSBombActor, ExplodeDelay), METADATA_PARAMS(Z_Construct_UClass_AFPSBombActor_Statics::NewProp_ExplodeDelay_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AFPSBombActor_Statics::NewProp_ExplodeDelay_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AFPSBombActor_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFPSBombActor_Statics::NewProp_RadialForceComp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFPSBombActor_Statics::NewProp_BombBox,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFPSBombActor_Statics::NewProp_BombMesh,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFPSBombActor_Statics::NewProp_ExplosionTemplate,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFPSBombActor_Statics::NewProp_ExplodeDelay,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AFPSBombActor_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AFPSBombActor>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AFPSBombActor_Statics::ClassParams = {
		&AFPSBombActor::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AFPSBombActor_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AFPSBombActor_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AFPSBombActor_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AFPSBombActor_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AFPSBombActor()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AFPSBombActor_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AFPSBombActor, 3740905819);
	template<> FPSGAME_API UClass* StaticClass<AFPSBombActor>()
	{
		return AFPSBombActor::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AFPSBombActor(Z_Construct_UClass_AFPSBombActor, &AFPSBombActor::StaticClass, TEXT("/Script/FPSGame"), TEXT("AFPSBombActor"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AFPSBombActor);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
