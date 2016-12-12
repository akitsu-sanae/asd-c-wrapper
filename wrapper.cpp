/*============================================================================
  Copyright (C) 2016 akitsu sanae
  https://github.com/akitsu-sanae/asd-c-wrapper
  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
============================================================================*/

#include "Altseed.h"

extern "C" {
    typedef struct {
        std::shared_ptr<asd::TextureObject2D> inner;
    } AsdTextureObject2dImpl;

    typedef struct {
        std::shared_ptr<asd::Texture2D> inner;
    } AsdTexture2dImpl;

    bool asd_initialize(const char* title, int width, int height) {
        return asd::Engine::Initialize(asd::ToAString(title).c_str(), width, height, asd::EngineOption{});
    }
    bool asd_do_events() {
        return asd::Engine::DoEvents();
    }
    void asd_update() {
        asd::Engine::Update();
    }
    void asd_terminate() {
        return asd::Engine::Terminate();
    }

    // asd::TextureObject2D::new
    AsdTextureObject2dImpl* asd_texture_object2d_create() {
        return new AsdTextureObject2dImpl{ std::make_shared<asd::TextureObject2D>() };
    }
    // asd::TextureObject2D::delete
    void asd_texture_object2d_free(AsdTextureObject2dImpl* obj) {
        delete obj;
    }
    // asd::TextureObject2D::setTexture
    void asd_texture_object2d_set_texture(AsdTextureObject2dImpl* obj, AsdTexture2dImpl* tex) {
        obj->inner->SetTexture(tex->inner);
    }


    AsdTexture2dImpl* asd_texture2d_create(const char* path) {
        return new AsdTexture2dImpl{ asd::Engine::GetGraphics()->CreateTexture2D(asd::ToAString(path).c_str()) };
    }
    void asd_texture2d_free(AsdTexture2dImpl* texture) {
        delete texture;
    }

    void asd_add_object2d(AsdTextureObject2dImpl* object) {
        asd::Engine::AddObject2D(object->inner);
    }
}
