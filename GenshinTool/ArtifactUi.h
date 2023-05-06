#pragma once

#include "Artifact.h"

class ArtifactUi
{
private:
	Artifact dropArtifact(int selectHouse, short star);
	void showArtifact(Artifact artifact, int coordX, int coordY);
	void showLevelUp(Artifact last, Artifact current, int coordX, int coordY);

public:
	void showUi();

	//刷取升级
	void showLevelUpUi();
	//合成台合成
	void showCraftUi();
};