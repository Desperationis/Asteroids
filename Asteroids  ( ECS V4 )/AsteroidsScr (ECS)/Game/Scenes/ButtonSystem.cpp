#include "ButtonSystem.h"
#include "../Systems/InputSystem/InputSystem.h"

ComponentMap<SDL_Texture*> ButtonSystem::textures;
ComponentMap<Font> ButtonSystem::texts;
ComponentMap<SceneManager::Scenes> ButtonSystem::scenes;
ComponentMap<Switch> ButtonSystem::switches;
ComponentMap<Button> ButtonSystem::buttons;


void ButtonSystem::allocateID(const EntityID& id, const ButtonInfo& info) {
	buttons[id] = Button{ };
	auto& currentButton = ButtonSystem::buttons[id];
	currentButton.dest = info.dest;
	currentButton.mask = info.mask;

	if ((info.mask & COMPONENT_TEXTURED) == COMPONENT_TEXTURED) {
		textures[id] = TM::LoadTexture(info.file);
		SDL_QueryTexture(textures[id], NULL, NULL, &currentButton.dest.w, &currentButton.dest.h);
	}
	if ((info.mask & COMPONENT_DRAWN) == COMPONENT_DRAWN) {
		texts[id] = Font{ };
		currentButton.bg_color = info.bg_color;
		texts[id].fontColor = info.color;
		FontSystem::setUp(texts[id], info.fontFile, info.ptsize);
		FontSystem::setText(texts[id], info.text);
		texts[id].fontDest.x = (currentButton.dest.x + (currentButton.dest.w / 2)) - (texts[id].fontDest.w / 2);
		texts[id].fontDest.y = (currentButton.dest.y + (currentButton.dest.h / 2)) - (texts[id].fontDest.h / 2);
	}
	if ((info.mask & COMPONENT_SCENE) == COMPONENT_SCENE) {
		scenes[id] = info.scene;
	}
	if ((info.mask & COMPONENT_SWITCH) == COMPONENT_SWITCH) {
		switches[id] = Switch{ };
	}
}

void ButtonSystem::render() {
	for (auto it = buttons.begin(); it != buttons.end(); it++) {
		if ((it.value().mask & COMPONENT_TEXTURED) == COMPONENT_TEXTURED) {
			TM::DrawTexture(textures[it.key()], it.value().dest);
		}
		if ((it.value().mask & COMPONENT_DRAWN) == COMPONENT_DRAWN) {
			SDL_SetRenderDrawColor(Game::renderer, it.value().bg_color.r, it.value().bg_color.g, it.value().bg_color.b, 255);
			SDL_RenderFillRect(Game::renderer, &it.value().dest);
			TM::DrawTexture(texts[it.key()].fontTexture, texts[it.key()].fontDest);
		}
	}
}

bool pressed = false;
void ButtonSystem::update() {
	bool clear = false;
	if (InputSystem::mouse[InputSystem::LEFT] && !pressed) {
		for (auto it = ButtonSystem::buttons.begin(); it != ButtonSystem::buttons.end(); it++) {
			if (InputSystem::mouse[InputSystem::X] < it.value().dest.x + it.value().dest.w &&
				InputSystem::mouse[InputSystem::X] > it.value().dest.x &&
				InputSystem::mouse[InputSystem::Y] < it.value().dest.y + it.value().dest.h &&
				InputSystem::mouse[InputSystem::Y] > it.value().dest.y) {

				if ((ButtonSystem::buttons[it.key()].mask & COMPONENT_SWITCH) == COMPONENT_SWITCH) {
					ButtonSystem::switches[it.key()]._switch_ = !ButtonSystem::switches[it.key()]._switch_;
				}

				if (ButtonSystem::scenes[it.key()] != SceneManager::NONE) {
					SceneManager::currentScene = ButtonSystem::scenes[it.key()];
					clear = true;
				}
			}
		}
	}
	pressed = InputSystem::mouse[InputSystem::LEFT];
	if (clear) free();
}

void ButtonSystem::free() {
	textures.clear();
	switches.clear();
	texts.clear();
	buttons.clear();
	scenes.clear();
}