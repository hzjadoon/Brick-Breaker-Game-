
## Flowchart

```plaintext
           +--------------------+
           | Start              |
           +--------------------+
                    |
                    v
   +----------------------------------+
   | Initialize game window, load     |
   | textures, sounds, fonts, and     |
   | create game objects              |
   +----------------------------------+
                    |
                    v
           +--------------------+
           | Display Main Menu  |
           +--------------------+
                    |
                    v
         +----------------------+
         | Handle Menu Input    |
         +----------------------+
                    |
         +----------+----------+
         |                     |
         v                     v
+-------------------+  +-----------------+
| Start Game        |  | Show About Us   |
+-------------------+  +-----------------+
         |                     |
         v                     v
+-------------------+  +-----------------+
| Enter Game Loop   |  | Handle About Us |
+-------------------+  +-----------------+
         |                     |
         v                     v
+-------------------+  +-----------------+
| Handle Input,     |  | Return to Menu  |
| Update Positions  |  +-----------------+
| and Collisions    |
+-------------------+
         |
         v
+-------------------+
| Check for Win or  |
| Game Over         |
+-------------------+
         |
         v
+-------------------+
| Display Win or    |
| Game Over Screen  |
+-------------------+
         |
         v
+-------------------+
| Return to Menu    |
+-------------------+
