#!/usr/bin/env python3

import os
import json
from datetime import datetime

class GameLauncher:
    def __init__(self):
        self.game_title = "OpenWorld Mobile"
        self.version = "1.0"
        self.platform = "Mobile"
        self.game_data = {
            "player_money": 1000,
            "player_reputation": 0,
            "wanted_level": 0,
            "health": 100,
            "stamina": 100,
            "playtime": 0
        }

    def display_splash(self):
        print("="*50)
        print(f"  {self.game_title} v{self.version}")
        print("  Open-World Sandbox Game")
        print("="*50)
        print()

    def main_menu(self):
        while True:
            print("\n[MAIN MENU]")
            print("1. Play Game")
            print("2. Continue")
            print("3. Settings")
            print("4. Exit")
            print()
            choice = input("Select option (1-4): ").strip()

            if choice == "1":
                self.new_game()
            elif choice == "2":
                self.continue_game()
            elif choice == "3":
                self.settings()
            elif choice == "4":
                self.exit_game()
            else:
                print("Invalid choice!")

    def new_game(self):
        print("\n" + "="*50)
        print("STARTING NEW GAME...")
        print("="*50)
        print()
        print("Welcome to OpenWorld!")
        print()
        self.show_stats()
        self.show_controls()
        self.gameplay_loop()

    def continue_game(self):
        print("\n[LOADING GAME]")
        self.show_stats()
        self.gameplay_loop()

    def show_stats(self):
        print("\n[PLAYER STATS]")
        print(f"  💰 Money: ${self.game_data['player_money']}")
        print(f"  🏆 Reputation: {self.game_data['player_reputation']}")
        print(f"  ⭐ Wanted Level: {self.game_data['wanted_level']}/5")
        print(f"  ❤️ Health: {self.game_data['health']}/100")
        print(f"  ⚡ Stamina: {self.game_data['stamina']}/100")
        print(f"  ⏱️ Playtime: {self.game_data['playtime']}h")
        print()

    def show_controls(self):
        print("[MOBILE CONTROLS]")
        print("  👆 Left Joystick = Move")
        print("  👆 Right Button = Attack")
        print("  👆 Double Tap = Run")
        print("  👆 Swipe = Rotate Camera")
        print()

    def gameplay_loop(self):
        print("\n" + "="*50)
        print("GAME STARTED!")
        print("="*50)
        print()

        actions = [
            "1. Complete a Mission (+$500, +10 Rep)",
            "2. Commit a Crime (+1 Star, +$200)",
            "3. Escape Police (0 Stars)",
            "4. Attack NPC (-10 Health, +$100)",
            "5. Rest (Recover Stamina)",
            "6. Return to Menu"
        ]

        while True:
            print("\n[IN-GAME]")
            for action in actions:
                print(action)
            print()

            choice = input("Choose action (1-6): ").strip()

            if choice == "1":
                self.mission()
            elif choice == "2":
                self.commit_crime()
            elif choice == "3":
                self.escape_police()
            elif choice == "4":
                self.attack_npc()
            elif choice == "5":
                self.rest()
            elif choice == "6":
                break
            else:
                print("Invalid action!")

    def mission(self):
        print("\n✅ Mission Completed!")
        self.game_data['player_money'] += 500
        self.game_data['player_reputation'] += 10
        print(f"   +$500 | +10 Rep")
        print(f"   Total: ${self.game_data['player_money']} | Rep: {self.game_data['player_reputation']}")

    def commit_crime(self):
        print("\n🚨 CRIME COMMITTED!")
        self.game_data['wanted_level'] = min(5, self.game_data['wanted_level'] + 1)
        self.game_data['player_money'] += 200
        stars = "⭐" * self.game_data['wanted_level']
        print(f"   Wanted: {stars}")
        print(f"   +$200")

    def escape_police(self):
        if self.game_data['wanted_level'] > 0:
            print("\n🏃 Escaped Police!")
            self.game_data['wanted_level'] = 0
            print("   Wanted Level: 0 ⭐")
        else:
            print("\n❌ No police are chasing you!")

    def attack_npc(self):
        print("\n⚔️ Attack!")
        self.game_data['health'] -= 10
        self.game_data['player_money'] += 100
        print(f"   -10 Health | +$100")
        print(f"   Health: {self.game_data['health']}/100")

    def rest(self):
        print("\n😴 Resting...")
        self.game_data['stamina'] = 100
        self.game_data['health'] = min(100, self.game_data['health'] + 20)
        print(f"   Stamina: 100/100")
        print(f"   Health: {self.game_data['health']}/100")

    def settings(self):
        print("\n[SETTINGS]")
        print("1. Graphics: Mobile Optimized")
        print("2. Audio: ON")
        print("3. Haptics: ON")
        print("4. Back")
        choice = input("\nSelect (1-4): ").strip()
        if choice != "4":
            print("Settings saved!")

    def exit_game(self):
        print("\n" + "="*50)
        print("Thanks for playing OpenWorld!")
        print(f"Total Playtime: {self.game_data['playtime']}h")
        print(f"Final Money: ${self.game_data['player_money']}")
        print(f"Final Reputation: {self.game_data['player_reputation']}")
        print("="*50)
        print()
        exit()

def main():
    launcher = GameLauncher()
    launcher.display_splash()
    launcher.main_menu()

if __name__ == "__main__":
    main()
