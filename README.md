# ErysEdits
Several mods I would've made into smaller standalone mods when I was an ignorant Geode developer. (And I still probably am by several accounts, but who's keeping track? `/j`)

## Features
- Various Info Label tweaks, including improved readibility, conditiona displays, and debug text logging

![demoOne](https://github.com/RayDeeUx/ErysEdits/blob/main/resources/demoOne.png)
![demoOnePointFive](https://github.com/RayDeeUx/ErysEdits/blob/main/resources/demoOnePointFive.png)
![demoOnePointSeventyFive](https://github.com/RayDeeUx/ErysEdits/blob/main/resources/demoOnePointSeventyFive.png)
![demoOnePointEightHundredSeventyFive](https://github.com/RayDeeUx/ErysEdits/blob/main/resources/demoOnePointEightHundredSeventyFive.png)

- Viewing level descriptions from level lists and daily/weekly levels (compatible with nearly every possible mod that edits the LevelCell, including Cvolton's BetterInfo + Compact Level Lists, cdc's Level Thumbnails, n's Level Pronouns, and dankmeme's Globed)

![demoTwo](https://github.com/RayDeeUx/ErysEdits/blob/main/resources/demoTwo.png)
![demoTwoPointFive](https://github.com/RayDeeUx/ErysEdits/blob/main/resources/demoTwoPointFive.png)
![demoTwoPointSeventyFive](https://github.com/RayDeeUx/ErysEdits/blob/main/resources/demoTwoPointSeventyFive.png)

- Compact local levels list (with some code borrowed from Cvolton, compatible with LevelSize by hiimjustin000)

![demoThree](https://github.com/RayDeeUx/ErysEdits/blob/main/resources/demoThree.png)

- Hide "Level Complete" visuals (except particles, use your local mod menu to hide those)

![demoFour](https://github.com/RayDeeUx/ErysEdits/blob/main/resources/demoFour.png)

- Disabling the cube jump animation in platformer levels (hitbox trail for reference)

![demoFive](https://github.com/RayDeeUx/ErysEdits/blob/main/resources/demoFive.png)

- Hidden progress bar and percentage on unverified local levels
- Force levels to stop music on death
- Force levels to play your death SFX on death (compatible with Adam_729's Random Death Sounds and ControlVanillaSFX, see mod settings for more details)
- Various keybinds to make navigating Geometry Dash feel a lot less repetive (Ctrl + S to save, Ctrl + R to refresh, Alt + Left/Right to navigate between layers with pages, Shift + Left/Right to go to the first or last page, etc)
- Disable Shake, Pulse, Area Tint, SFX, and Edit SFX triggers
- Compact view of user profile comments/posts

## Special Thanks
- [acaruso](https://gdbrowser.com/u/25012294), for moral support + massive optimizations in codebase during development
- [Cvolton](https://gdbrowser.com/u/761691), for lending their C++ knowledge and allowing me to reuse/adapt some of their code from BetterEdit, Misc Bugfixes, and Compact Lists
- [Alphalaneous](https://gdbrowser.com/u/1139015) and [dankmeme](https://gdbrowser.com/u/9735891), for supplemental CMake/C++ expertise
- [SpaghettDev](https://gdbrowser.com/u/7670168) and [Prevter](https://gdbrowser.com/u/7696536), for finding memory address bindings that fully fleshed out some features (`0x305630` for `SecretLayer2::create()`;  `0x276180` and `0x276170`, for `LikeItemLayer::onDislike()` and `LikeItemLayer::onLike()` respectively)
- [Cooper](https://gdbrowser.com/u/21207551), for allowing me to reuse code for custom setting headers
- [sofabeddd](https://gdbrowser.com/u/7976112), for the occasional reality check