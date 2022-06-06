#include "pch.h"
#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif


#include "BoxCollider.h"
#include "FpsCounter.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "InputManager.h"
#include "Minigin.h"
#include "PPComponent.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ServiceLocator.h"
#include "TextComponent.h"
#include "IngredientComponent.h"
#include "JsonReader.h"
#include "MovementComponent.h"
#include "EnemyComponent.h"
#include "ResetComponent.h"
#include "SpriteComponent.h"
#include "RigidBody.h"
#include "ScoreDisplayComponent.h"
#include "UILevelLoadingButton.h"

enum class EIngredient
{
	TopBurger, BottomBurger, Cheese, Burger, Tomato, Salad
};
void SpawnIngredient(dae::Scene& scene,EIngredient item, SDL_Point spawnPoint, ScoreDisplayComponent* scoreComp)
{
	SpriteComponent::SpritePart sp{};
	switch (item)
	{
	case EIngredient::TopBurger:
		sp = SpriteComponent::SpritePart({ 112,49,31,7  });
		break;
	case EIngredient::BottomBurger: 
		sp = SpriteComponent::SpritePart({ 112,57,31,7 });
		break;
	case EIngredient::Cheese: 
		sp = SpriteComponent::SpritePart({ 112,65,31,7 });
		break;
	case EIngredient::Burger: 
		sp = SpriteComponent::SpritePart({ 112,73,31,7 });
		break;
	case EIngredient::Tomato: 
		sp = SpriteComponent::SpritePart({ 112,81,31,7 });
		break;
	case EIngredient::Salad: 
		sp = SpriteComponent::SpritePart({ 112,89,31,7 });
		break;
	}
	const auto burgerObj = std::make_shared<dae::GameObject>("Ingredient");
	burgerObj->SetPosition(static_cast<float>(spawnPoint.x)*2 + 112, static_cast<float>(spawnPoint.y) * 2 + 40);
	/*const auto spriteComp = */burgerObj->AddComponent(new SpriteComponent(burgerObj.get(), "BurgerTimeSpriteSheet.png", sp,{2,2}));
	/*const auto ingreComp = */burgerObj->AddComponent<IngredientComponent>()->GetSubject()->AddObserver(scoreComp);
	/*const auto rigid = */burgerObj->AddComponent(new RigidBody(burgerObj.get(),{0,15,0}));
	/*const auto boxCol = */burgerObj->AddComponent(new BoxCollider(burgerObj.get(),{0,0,sp.SrcRect.w * 2,sp.SrcRect.h * 2}));
	scene.Add(burgerObj);
}

void DefaultLevelFunctionality(dae::Scene& scene)
{
#pragma region FPSCounter
	{
		const auto fpsGameObject = std::make_shared<dae::GameObject>();
		const auto textComp = new dae::TextComponent(fpsGameObject.get(), " ", dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36));
		fpsGameObject->AddComponent(textComp);
		fpsGameObject->AddComponent<dae::FpsCounter>();

		scene.Add(fpsGameObject);
	}
#pragma endregion

}

void SpawnLevel01(dae::Scene& scene)
{
	DefaultLevelFunctionality(scene);
	const auto bt = std::make_shared<dae::GameObject>();
	bt->AddComponent(new UILevelLoadingButton(bt.get(), scene.GetName(), { 0,0,600,200 }, { 100,450,90,30 }, "ButtonSprite.png"));
	scene.Add(bt);

#pragma region Observers

	const auto resetObject = std::make_shared<dae::GameObject>();
	const auto resetComp = resetObject->AddComponent<ResetComponent>();
	scene.Add(resetObject);

	const auto scoreObj = std::make_shared<dae::GameObject>();
	const auto scoreText = new dae::TextComponent(scoreObj.get(), " ", dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20));
	scoreText->SetPosition(300, 0);
	scoreObj->AddComponent(scoreText);
	const auto scoreComp = scoreObj->AddComponent<ScoreDisplayComponent>();
	scene.Add(scoreObj);

	const auto healthObject = std::make_shared<dae::GameObject>();
	const auto healthComp = healthObject->AddComponent<HealthComponent>();
	healthComp->GetSubject()->AddObserver(scoreComp);
	healthComp->GetSubject()->AddObserver(resetComp);
	scene.Add(healthObject);

#pragma endregion

#pragma region LevelObj
	{
		const auto levelObj = std::make_shared<dae::GameObject>("Level");

		//SpriteRenderer
		SpriteComponent* spriteRenderer = new SpriteComponent(levelObj.get(), "BurgerTimeLevels.png", SpriteComponent::SpritePart({ 0,0,208,200 }), .3f, { 112,40,416,400 });
		levelObj->AddComponent(spriteRenderer);
		scene.Add(levelObj);
	}
#pragma endregion

#pragma region BurgerObjs level01
	SpawnIngredient(scene, EIngredient::TopBurger, { 64,8 }, scoreComp);
	SpawnIngredient(scene, EIngredient::TopBurger, { 112,8 }, scoreComp);
	SpawnIngredient(scene, EIngredient::TopBurger, { 160,8 }, scoreComp);
	SpawnIngredient(scene, EIngredient::TopBurger, { 16,40 }, scoreComp);

	SpawnIngredient(scene, EIngredient::Salad, { 112,40 }, scoreComp);

	SpawnIngredient(scene, EIngredient::Salad, { 160,40 }, scoreComp);
	SpawnIngredient(scene, EIngredient::Salad, { 16,72 }, scoreComp);
	SpawnIngredient(scene, EIngredient::Salad, { 64,88 }, scoreComp);

	SpawnIngredient(scene, EIngredient::Burger, { 112,120 }, scoreComp);
	SpawnIngredient(scene, EIngredient::Burger, { 160,72 }, scoreComp);
	SpawnIngredient(scene, EIngredient::Burger, { 16,120 }, scoreComp);
	SpawnIngredient(scene, EIngredient::Burger, { 64,120 }, scoreComp);

	SpawnIngredient(scene, EIngredient::BottomBurger, { 160,104 }, scoreComp);
	SpawnIngredient(scene, EIngredient::BottomBurger, { 16,152 }, scoreComp);
	SpawnIngredient(scene, EIngredient::BottomBurger, { 64,152 }, scoreComp);
	SpawnIngredient(scene, EIngredient::BottomBurger, { 112,152 }, scoreComp);
#pragma endregion


#pragma region PeterPepper
	//peterPepper Object

	const auto peterPepperObj = std::make_shared<dae::GameObject>("Player");
	peterPepperObj->SetPosition(300, 270);
	resetComp->AddObject(peterPepperObj.get());

	//TextComponent
	const auto textCompPP = peterPepperObj->AddComponent<dae::TextComponent>();
	textCompPP->SetPosition(50, 100);
	textCompPP->SetText(std::to_string(healthComp->GetHealth()));

	//PeterPepperComponent
	const auto peterPepperComp = peterPepperObj->AddComponent<PPComponent>();
	peterPepperComp->GetSubject()->AddObserver(healthComp);

	//SpriteRenderer
	peterPepperObj->AddComponent(new SpriteComponent(peterPepperObj.get(), "BurgerTimeSpriteSheet.png", SpriteComponent::SpritePart(SDL_Point{ 48,16 }, 16), .3f, { 0,0,20,20 }));

	//RigidBody
	peterPepperObj->AddComponent(new RigidBody(peterPepperObj.get(), { 20,20,20 }));
	peterPepperObj->AddComponent<MovementComponent>();

	//BoxCollider
	peterPepperObj->AddComponent(new BoxCollider(peterPepperObj.get(), 20));

	scene.Add(peterPepperObj);

#pragma endregion

#pragma region Mr_HotDog

	const auto mrHotDogObj = std::make_shared<dae::GameObject>("Enemy");
	mrHotDogObj->SetPosition(150, 50);
	resetComp->AddObject(mrHotDogObj.get());

	//SpriteRenderer
	mrHotDogObj->AddComponent(new SpriteComponent(mrHotDogObj.get(), "BurgerTimeSpriteSheet.png", SpriteComponent::SpritePart(2, 1, SDL_Point{ 16,32 }, 16), .3f, { 0,0,20,20 }));
	//movecomp
	mrHotDogObj->AddComponent<MovementComponent>();
	mrHotDogObj->AddComponent(new RigidBody(mrHotDogObj.get(), { 10,10,10 }));

	//BoxCollider
	mrHotDogObj->AddComponent(new BoxCollider(mrHotDogObj.get(), 20));

	const auto hotDogComp = mrHotDogObj->AddComponent<EnemyComponent>();
	hotDogComp->SetTarget({ peterPepperObj.get() });
	scene.Add(mrHotDogObj);


#pragma endregion
	JsonReader::GetInstance().ReadFile(scene, "../Data/Level01.json");
}
void Spawnlevel02(dae::Scene& scene)
{
	DefaultLevelFunctionality(scene);
	const auto bt = std::make_shared<dae::GameObject>();
	bt->AddComponent(new UILevelLoadingButton(bt.get(), scene.GetName(), { 0,0,600,200 }, { 100,450,90,30 }, "ButtonSprite.png"));
	scene.Add(bt);

#pragma region Observers

	const auto resetObject = std::make_shared<dae::GameObject>();
	const auto resetComp = resetObject->AddComponent<ResetComponent>();
	scene.Add(resetObject);

	const auto scoreObj = std::make_shared<dae::GameObject>();
	const auto scoreText = new dae::TextComponent(scoreObj.get(), " ", dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20));
	scoreText->SetPosition(300, 0);
	scoreObj->AddComponent(scoreText);
	const auto scoreComp = scoreObj->AddComponent<ScoreDisplayComponent>();
	scene.Add(scoreObj);

	const auto healthObject = std::make_shared<dae::GameObject>();
	const auto healthComp = healthObject->AddComponent<HealthComponent>();
	healthComp->GetSubject()->AddObserver(scoreComp);
	healthComp->GetSubject()->AddObserver(resetComp);
	scene.Add(healthObject);


#pragma endregion

#pragma region LevelObj
	{
		const auto levelObj = std::make_shared<dae::GameObject>("Level");

		//SpriteRenderer
		SpriteComponent* spriteRenderer = new SpriteComponent(levelObj.get(), "BurgerTimeLevels.png", SpriteComponent::SpritePart({ 0,416,208,200 }), .3f, { 112,40,416,400 });
		levelObj->AddComponent(spriteRenderer);
		scene.Add(levelObj);
	}
#pragma endregion

#pragma region BurgerObjs level02
	SpawnIngredient(scene, EIngredient::TopBurger, { 16,8 }, scoreComp);
	SpawnIngredient(scene, EIngredient::TopBurger, { 64,8 }, scoreComp);
	SpawnIngredient(scene, EIngredient::TopBurger, { 112,8 }, scoreComp);
	SpawnIngredient(scene, EIngredient::TopBurger, { 160,8 }, scoreComp);

	SpawnIngredient(scene, EIngredient::Cheese, { 16,24 }, scoreComp);
	SpawnIngredient(scene, EIngredient::Salad, { 64, 24 }, scoreComp);
	SpawnIngredient(scene, EIngredient::Tomato, { 112,24 }, scoreComp);
	SpawnIngredient(scene, EIngredient::Cheese, { 160,24 }, scoreComp);

	SpawnIngredient(scene, EIngredient::Tomato, { 16,40 }, scoreComp);
	SpawnIngredient(scene, EIngredient::Tomato, { 64, 40 }, scoreComp);
	SpawnIngredient(scene, EIngredient::Salad, { 112,40 }, scoreComp);
	SpawnIngredient(scene, EIngredient::Salad, { 160,40 }, scoreComp);

	SpawnIngredient(scene, EIngredient::Salad, { 16,56 }, scoreComp);
	SpawnIngredient(scene, EIngredient::Burger, { 64, 56 }, scoreComp);
	SpawnIngredient(scene, EIngredient::Tomato, { 112,56 }, scoreComp);
	SpawnIngredient(scene, EIngredient::Burger, { 160,56 }, scoreComp);

	SpawnIngredient(scene, EIngredient::Burger, { 16,72 }, scoreComp);
	SpawnIngredient(scene, EIngredient::Tomato, { 64, 72 }, scoreComp);
	SpawnIngredient(scene, EIngredient::Burger, { 112,72 }, scoreComp);
	SpawnIngredient(scene, EIngredient::Tomato, { 160,72 }, scoreComp);

	SpawnIngredient(scene, EIngredient::Tomato, { 16,88 }, scoreComp);
	SpawnIngredient(scene, EIngredient::Salad, { 64, 88 }, scoreComp);
	SpawnIngredient(scene, EIngredient::Salad, { 112,88 }, scoreComp);
	SpawnIngredient(scene, EIngredient::Tomato, { 160,88 }, scoreComp);

	SpawnIngredient(scene, EIngredient::BottomBurger, { 16,104 }, scoreComp);
	SpawnIngredient(scene, EIngredient::BottomBurger, { 64, 104 }, scoreComp);
	SpawnIngredient(scene, EIngredient::BottomBurger, { 112,104 }, scoreComp);
	SpawnIngredient(scene, EIngredient::BottomBurger, { 160,104 }, scoreComp);
#pragma endregion
#pragma region PeterPepper
	//peterPepper Object

	const auto peterPepperObj = std::make_shared<dae::GameObject>("Player");
	peterPepperObj->SetPosition(300, 270);
	resetComp->AddObject(peterPepperObj.get());

	//TextComponent
	const auto textCompPP = peterPepperObj->AddComponent<dae::TextComponent>();
	textCompPP->SetPosition(50, 100);
	textCompPP->SetText(std::to_string(healthComp->GetHealth()));

	//PeterPepperComponent
	const auto peterPepperComp = peterPepperObj->AddComponent<PPComponent>();
	peterPepperComp->GetSubject()->AddObserver(healthComp);

	//SpriteRenderer
	peterPepperObj->AddComponent(new SpriteComponent(peterPepperObj.get(), "BurgerTimeSpriteSheet.png", SpriteComponent::SpritePart(SDL_Point{ 48,16 }, 16), .3f, { 0,0,20,20 }));

	//RigidBody
	peterPepperObj->AddComponent(new RigidBody(peterPepperObj.get(), { 20,20,20 }));
	peterPepperObj->AddComponent<MovementComponent>();

	//BoxCollider
	peterPepperObj->AddComponent(new BoxCollider(peterPepperObj.get(), 20));

	scene.Add(peterPepperObj);

#pragma endregion

#pragma region Mr_HotDog

	const auto mrHotDogObj = std::make_shared<dae::GameObject>("Enemy");
	mrHotDogObj->SetPosition(150, 50);
	resetComp->AddObject(mrHotDogObj.get());

	//SpriteRenderer
	mrHotDogObj->AddComponent(new SpriteComponent(mrHotDogObj.get(), "BurgerTimeSpriteSheet.png", SpriteComponent::SpritePart(2, 1, SDL_Point{ 16,32 }, 16), .3f, { 0,0,20,20 }));
	//movecomp
	mrHotDogObj->AddComponent<MovementComponent>();
	mrHotDogObj->AddComponent(new RigidBody(mrHotDogObj.get(), { 10,10,10 }));

	//BoxCollider
	mrHotDogObj->AddComponent(new BoxCollider(mrHotDogObj.get(), 20));

	const auto hotDogComp = mrHotDogObj->AddComponent<EnemyComponent>();
	hotDogComp->SetTarget({ peterPepperObj.get() });
	scene.Add(mrHotDogObj);


#pragma endregion
	JsonReader::GetInstance().ReadFile(scene, "../Data/Level02.json");
}
void Spawnlevel03(dae::Scene& scene)
{
	DefaultLevelFunctionality(scene);
	const auto bt = std::make_shared<dae::GameObject>();
	bt->AddComponent(new UILevelLoadingButton(bt.get(), scene.GetName(), { 0,0,600,200 }, { 100,450,90,30 }, "ButtonSprite.png"));
	scene.Add(bt);

#pragma region Observers

	const auto resetObject = std::make_shared<dae::GameObject>();
	const auto resetComp = resetObject->AddComponent<ResetComponent>();
	scene.Add(resetObject);

	const auto scoreObj = std::make_shared<dae::GameObject>();
	const auto scoreText = new dae::TextComponent(scoreObj.get(), " ", dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20));
	scoreText->SetPosition(300, 0);
	scoreObj->AddComponent(scoreText);
	const auto scoreComp = scoreObj->AddComponent<ScoreDisplayComponent>();
	scene.Add(scoreObj);

	const auto healthObject = std::make_shared<dae::GameObject>();
	const auto healthComp = healthObject->AddComponent<HealthComponent>();
	healthComp->GetSubject()->AddObserver(scoreComp);
	healthComp->GetSubject()->AddObserver(resetComp);
	scene.Add(healthObject);


#pragma endregion

#pragma region LevelObj
	{
		const auto levelObj = std::make_shared<dae::GameObject>("Level");

		//SpriteRenderer
		SpriteComponent* spriteRenderer = new SpriteComponent(levelObj.get(), "BurgerTimeLevels.png", SpriteComponent::SpritePart({ 216,416,208,200 }), .3f, { 112,40,416,400 });
		levelObj->AddComponent(spriteRenderer);
		scene.Add(levelObj);
	}
#pragma endregion

#pragma region BurgerObjs level03
	SpawnIngredient(scene, EIngredient::TopBurger, { 64,8 }, scoreComp);
	SpawnIngredient(scene, EIngredient::TopBurger, { 112,8 }, scoreComp);

	SpawnIngredient(scene, EIngredient::Salad, { 64, 24 }, scoreComp);
	SpawnIngredient(scene, EIngredient::Tomato, { 112,24 }, scoreComp);

	SpawnIngredient(scene, EIngredient::Tomato, { 64, 40 }, scoreComp);
	SpawnIngredient(scene, EIngredient::Salad, { 112,40 }, scoreComp);

	SpawnIngredient(scene, EIngredient::Burger, { 64, 56 }, scoreComp);
	SpawnIngredient(scene, EIngredient::Tomato, { 112,56 }, scoreComp);

	SpawnIngredient(scene, EIngredient::Tomato, { 64, 72 }, scoreComp);
	SpawnIngredient(scene, EIngredient::Burger, { 112,72 }, scoreComp);

	SpawnIngredient(scene, EIngredient::Salad, { 64, 88 }, scoreComp);
	SpawnIngredient(scene, EIngredient::Salad, { 112,88 }, scoreComp);

	SpawnIngredient(scene, EIngredient::BottomBurger, { 64, 104 }, scoreComp);
	SpawnIngredient(scene, EIngredient::BottomBurger, { 112,104 }, scoreComp);
#pragma endregion
#pragma region PeterPepper
	//peterPepper Object

	const auto peterPepperObj = std::make_shared<dae::GameObject>("Player");
	peterPepperObj->SetPosition(300, 270);
	resetComp->AddObject(peterPepperObj.get());

	//TextComponent
	const auto textCompPP = peterPepperObj->AddComponent<dae::TextComponent>();
	textCompPP->SetPosition(50, 100);
	textCompPP->SetText(std::to_string(healthComp->GetHealth()));

	//PeterPepperComponent
	const auto peterPepperComp = peterPepperObj->AddComponent<PPComponent>();
	peterPepperComp->GetSubject()->AddObserver(healthComp);

	//SpriteRenderer
	peterPepperObj->AddComponent(new SpriteComponent(peterPepperObj.get(), "BurgerTimeSpriteSheet.png", SpriteComponent::SpritePart(SDL_Point{ 48,16 }, 16), .3f, { 0,0,20,20 }));

	//RigidBody
	peterPepperObj->AddComponent(new RigidBody(peterPepperObj.get(), { 20,20,20 }));
	peterPepperObj->AddComponent<MovementComponent>();

	//BoxCollider
	peterPepperObj->AddComponent(new BoxCollider(peterPepperObj.get(), 20));

	scene.Add(peterPepperObj);

#pragma endregion

#pragma region Mr_HotDog
	{
		const auto mrHotDogObj = std::make_shared<dae::GameObject>("Enemy");
		mrHotDogObj->SetPosition(150, 50);
		resetComp->AddObject(mrHotDogObj.get());

		//SpriteRenderer
		mrHotDogObj->AddComponent(new SpriteComponent(mrHotDogObj.get(), "BurgerTimeSpriteSheet.png", SpriteComponent::SpritePart(2,1,SDL_Point{ 16,32 }, 16), .3f, { 0,0,20,20 }));
		//movecomp
		mrHotDogObj->AddComponent<MovementComponent>();
		mrHotDogObj->AddComponent(new RigidBody(mrHotDogObj.get(), { 10,10,10 }));

		//BoxCollider
		mrHotDogObj->AddComponent(new BoxCollider(mrHotDogObj.get(), 20));

		const auto hotDogComp = mrHotDogObj->AddComponent<EnemyComponent>();
		hotDogComp->SetTarget({ peterPepperObj.get() });
		scene.Add(mrHotDogObj);
	}
	{
		const auto mrHotDogObj = std::make_shared<dae::GameObject>("Enemy");
		mrHotDogObj->SetPosition(200, 67);
		resetComp->AddObject(mrHotDogObj.get());

		//SpriteRenderer
		mrHotDogObj->AddComponent(new SpriteComponent(mrHotDogObj.get(), "BurgerTimeSpriteSheet.png", SpriteComponent::SpritePart(2,1,SDL_Point{ 16,32 }, 16), .3f, { 0,0,20,20 }));
		//movecomp
		mrHotDogObj->AddComponent<MovementComponent>();
		mrHotDogObj->AddComponent(new RigidBody(mrHotDogObj.get(), { 10,10,10 }));

		//BoxCollider
		mrHotDogObj->AddComponent(new BoxCollider(mrHotDogObj.get(), 20));

		const auto hotDogComp = mrHotDogObj->AddComponent<EnemyComponent>();
		hotDogComp->SetTarget({ peterPepperObj.get() });
		hotDogComp->SetChar(EnemyComponent::EEnemy::Mr_Egg);
		scene.Add(mrHotDogObj);
	}
	{
		const auto mrHotDogObj = std::make_shared<dae::GameObject>("Enemy");
		mrHotDogObj->SetPosition(300, 50);
		resetComp->AddObject(mrHotDogObj.get());

		//SpriteRenderer
		mrHotDogObj->AddComponent(new SpriteComponent(mrHotDogObj.get(), "BurgerTimeSpriteSheet.png", SpriteComponent::SpritePart(2,1,SDL_Point{ 16,32 }, 16), .3f, { 0,0,20,20 }));
		//movecomp
		mrHotDogObj->AddComponent<MovementComponent>();
		mrHotDogObj->AddComponent(new RigidBody(mrHotDogObj.get(), { 10,10,10 }));

		//BoxCollider
		mrHotDogObj->AddComponent(new BoxCollider(mrHotDogObj.get(), 20));

		const auto hotDogComp = mrHotDogObj->AddComponent<EnemyComponent>();
		hotDogComp->SetTarget({ peterPepperObj.get() });
		hotDogComp->SetChar(EnemyComponent::EEnemy::Mr_Egg);
		scene.Add(mrHotDogObj);
	}


#pragma endregion
	JsonReader::GetInstance().ReadFile(scene, "../Data/Level03.json");
}

void LoadGame()
{
	dae::SceneManager::GetInstance().SetSpawnLevelFunc(SpawnLevel01,"Level01");
	dae::SceneManager::GetInstance().SetSpawnLevelFunc(Spawnlevel02,"Level02");
	dae::SceneManager::GetInstance().SetSpawnLevelFunc(Spawnlevel03,"Level03");

	dae::SceneManager::GetInstance().LoadScene("Level01");
	ServiceLocator::GetSoundSystem().AddToQueue("../Data/BgMusic.wav");
}

int main(int, char* []) {
	dae::Minigin engine;
	engine.Initialize();
	ServiceLocator::RegisterSoundSystem(new SDLSoundSystem());
	LoadGame();
	engine.Run();
	ServiceLocator::ReleaseSoundSystem();
	return 0;
}