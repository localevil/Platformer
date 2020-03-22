#include <stdio.h>
#include "engine.h"

int main()
{
	engine_options_t e_options;
	e_options.title = "Game";
	e_options.width = 680;
	e_options.height = 420;

	engine_t *engine = engine_init(&e_options);

	while (engine_is_running(engine))
	{
		engine_handle_events(engine);
		engine_update(engine);
		engine_render(engine);
	}
	engine_delete(engine);
}
