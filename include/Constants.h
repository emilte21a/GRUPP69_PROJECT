#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

namespace constants
{
	// Constants
	constexpr int gScreenWidth{640};
	constexpr int gScreenHeight{480};
	const int unitSize{32};
	// PATH TO YOUR RESOURCE FOLDER 'resources', 'gResPath'
	const std::string gResPath{"./resources/"};
	// PATH'S TO ALL YOUR EXTERNAL RESOURCES using 'gResPath'
	const std::string bg_str{gResPath + "images/bg.jpg"};
	const std::string gubbe_str{gResPath + "images/gubbe.png"};
	const std::string fiende_str{gResPath + "images/fiende.png"};
	const std::string idle_str{gResPath + "images/characteridle.png"};
	const std::string sample_str{gResPath + "sounds/sample.wav"};
	const std::string jump_str{gResPath + "sounds/jumpSoundEffect.wav"};
	const std::string arial_str{gResPath + "fonts/arial.ttf"};
}

#endif