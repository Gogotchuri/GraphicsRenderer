/*
 * RenderCommand.cpp
 *
 *  Created on: Dec 11, 2019
 *      Author: gogotchuri
 */

#include "RenderCommand.h"

std::shared_ptr<RendererAPI> RenderCommand::renderer_API = RendererAPI::create();
