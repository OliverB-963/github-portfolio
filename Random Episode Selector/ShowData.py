import sys
import os

class ShowData:
    def __init__(self):
        if getattr(sys, 'frozen', False):
            # If the application is run as a bundle (created by PyInstaller)
            self.path = os.path.dirname(sys.executable)
        else:
            # If the application is run as a script
            self.path = os.path.dirname(os.path.abspath(__file__))

        self.path += "\\"

        self.__shows = []
        self.__seasons = []
        self.__show_status = []
        self.__current_show = ""
        
        with open(self.path + "Data\\show_data.txt", 'r') as file:
            count = 0

            for line in file.readlines():
                line = line.strip()
                if count == 0:
                    self.__shows.append(line)
                    self.__seasons.append([])
                elif count == -1:
                    count = int(line) + 1
                else:
                    self.__seasons[len(self.__shows) - 1].append(int(line))
                count -= 1

        with open(self.path + "Data\\seen_shows_data.txt", 'r') as file:
            count = 0
            season_count = -1

            for line in file.readlines():
                line = line.strip()
                if count == -1:
                    count = int(line) + 1
                    self.__show_status.append([])
                    season_count += 1
                elif count != 0:
                    self.__show_status[season_count].append(ShowData.__retrieve_status_line(line))
                count -= 1
        
        with open(self.path + "Data\\system_data.txt", 'r') as file:
            self.__current_show = file.readline().strip()
    
    def __retrieve_status_line(line: str):
        if line == '':
            return []

        values = line.split('#')
        for i in range(len(values)):
            values[i] = int(values[i])
            
        return values

    def __format_status_line(listy: list):
        if len(listy) == 0:
            return ''

        count = 0
        listy_as_string = ""
        for item in listy:
            if count != 0:
                listy_as_string += '#'

            listy_as_string += str(item)
            
            count += 1

        return listy_as_string

    def get_show_names(self):
        return self.__shows

    def get_shows_seasons(self, show_name):
        return self.__seasons[self.__shows.index(show_name)]
    
    def get_shows_seasons_num(self, show_name):
        return len(self.__seasons[self.__shows.index(show_name)])
    
    def get_shows_seasons_episodes_num(self, show_name, season_index):
        return self.__seasons[self.__shows.index(show_name)][season_index]
    
    def get_shows_seasons_total(self, show_name):
        return sum(self.__seasons[self.__shows.index(show_name)])
    
    def get_seen_shows_seasons(self, show_name):
        return self.__show_status[self.__shows.index(show_name)]
    
    def get_episode_watched(self, show_name, season, episode):
        show_index = self.__shows.index(show_name)
        return self.__show_status[show_index][season][episode]
    
    def get_current_show(self):
        return self.__current_show
    
    def add_show(self, show_name):
        self.__shows.append(show_name)
        self.__seasons.append([])
        self.__show_status.append([])

    def add_season(self, show_name):
        show_index = self.__shows.index(show_name)
        self.__seasons[show_index].append(0)
        self.__show_status[show_index].append([])

    def delete_show(self, show_name):
        show_index = self.__shows.index(show_name)
        self.__shows.pop(show_index)
        self.__seasons.pop(show_index)
        self.__show_status.pop(show_index)

    def delete_season(self, show_name):
        show_index = self.__shows.index(show_name)
        self.__seasons[show_index].pop()
        self.__show_status[show_index].pop()

    def set_seasons(self, show_name, season_num):
        difference = season_num - self.get_shows_seasons_num(show_name)

        while difference != 0:
            if difference > 0:
                self.add_season(show_name)
                difference -= 1
            else:
                self.delete_season(show_name)
                difference += 1
    
    def change_episode_value(self, show_name, season_index, episode_value):
        show_index = self.__shows.index(show_name)
        current_season_episode_value = self.get_shows_seasons_episodes_num(show_name, season_index)
        self.__seasons[show_index][season_index] = episode_value

        if current_season_episode_value >= episode_value:
            self.__show_status[show_index][season_index] = self.__show_status[show_index][season_index][:episode_value]
        else:
            for _ in range(episode_value - current_season_episode_value):
                self.__show_status[show_index][season_index].append(0)

    def change_current_show(self, show_name):
        self.__current_show = show_name

    def change_episode_watched(self, show_name, season, episode, value):
        show_index = self.__shows.index(show_name)
        self.__show_status[show_index][season][episode] = value

    def show_exists(self, show_name):
        return show_name in self.__shows

    def save(self):
        with open(self.path + "Data\\show_data.txt", 'w') as file:
            count = 0
            for show_name in self.__shows:
                file.writelines(show_name + '\n')
                file.writelines(str(len(self.__seasons[count])) + '\n')
                
                for episodes_num in self.__seasons[count]:
                    file.writelines(str(episodes_num) + '\n')

                count += 1

        with open(self.path + "Data\\seen_shows_data.txt", 'w') as file:
            count = 0
            for show_name in self.__shows:
                file.writelines(show_name + '\n')
                file.writelines(str(len(self.__seasons[count])) + '\n')
                
                for season in self.__show_status[count]:
                    file.writelines(ShowData.__format_status_line(season) + '\n')

                count += 1
        
        with open(self.path + "Data\\system_data.txt", 'w') as file:
            file.writelines(self.__current_show + '\n')