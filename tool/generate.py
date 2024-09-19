#! /usr/bin/env python3

import os
import json
from itertools import permutations
from jinja2 import Template
from typing import List, Dict

class File(object):
    def __init__(self, path:str) -> None:
        self.__path = os.path.abspath(path)

    def path(self) -> str:
        return self.__path
    
    def filename(self) -> str:
        return os.path.basename(self.__path)
    
    def basename(self) -> str:
        return os.path.splitext(self.filename())[0]
    
    def dirpath(self) -> str:
        return os.path.dirname(self.__path)
    
    def join(self, *subs:str) -> 'File':
        return File(os.path.join(self.__path, *subs))
    
    def listdir(self,key:None=None) -> List[str]:
        files:List[str] = os.listdir(self.__path)
        files.sort(key=key)
        return files
    
    def open(self, mode:str="r") -> any:
        if not os.path.exists(self.dirpath()):
            os.makedirs(self.dirpath())

        return open(self.__path, mode)

    

class ThemeRenderer(object):
    def __init__(self, template:File) -> None:
        self.__template = template

    def sort_files(x):
        prior = ['common.qss', 'QWidget.qss']
        return prior.index(x) if x in prior else len(prior)

    def merge(self) -> str:
        templates:List[str] = []
        for filename in self.__template.listdir(ThemeRenderer.sort_files):
            with self.__template.join(filename).open() as fp:
                templates.append(fp.read())

        return "\n".join(templates)

    def render(self, palette:Dict[str,List[str]]) -> Dict[str,str]:
        palette = palette.copy()
        base:List[str] = palette.pop("Gray")
        colors:Dict[str,List[str]] = {}
        themes:Dict[str, str] = {}
        template:Template = Template(self.merge())
        for primary, secondary in permutations(palette, 2):
            colors["Primary"] = palette[primary]
            colors["Secondary"] = palette[secondary]
            themes[f"{primary}_{secondary}"] = template.render(base=base, colors=colors)

        return themes



class IconRenderer(object):
    def __init__(self, template:File) -> None:
        with template.open() as fp:
            self.__template:Template = Template(fp.read())

    def render(self, colors:List[str]) -> Dict[str,str]:
        icons:Dict[str,str] = {}
        for color in colors:
            icons[color] = self.__template.render(color=color)
        return icons



def render_resource_qrc(qrc:File, template:File, files:List[str]):
    with template.open() as fp:
        renderer:Template = Template(fp.read())

    with qrc.open("w") as fp:
        fp.write(renderer.render(files=files))

if __name__ == "__main__":
    tool_dir:File = File(os.path.dirname(__file__))
    template_dir:File = tool_dir.join("template")
    theme_template_dir:File = template_dir.join("theme")
    icon_template_dir:File = template_dir.join("icon")
    palette_file:File = tool_dir.join("palette.json")
    root_dir:File = tool_dir.join("..")
    resource_dir:File = root_dir.join("resource")
    theme_dir:File = resource_dir.join("theme")
    icon_dir:File = resource_dir.join("icon")
    
    with palette_file.open() as fp:
        dark_palette:Dict[str, List[str]] = json.loads(fp.read())
        light_palette:Dict[str, List[str]] = {key:list(reversed(dark_palette[key])) for key in dark_palette}

    theme_files:List[str] = []
    for theme_template in theme_template_dir.listdir():
        renderer:ThemeRenderer = ThemeRenderer(theme_template_dir.join(theme_template))
        
        # Dark
        themes:Dict[str, List[str]] = renderer.render(palette=dark_palette)
        for color in themes:
            theme_file:str = f"{File(theme_template).basename()}_Dark_{color}.qss"
            theme_files.append(theme_file)
            with theme_dir.join(theme_file).open("w") as fp:
                fp.write(themes[color])

        # Light
        themes:Dict[str, List[str]] = renderer.render(palette=light_palette)
        for color in themes:
            theme_file:str = f"{File(theme_template).basename()}_Light_{color}.qss"
            theme_files.append(theme_file)
            with theme_dir.join(theme_file).open("w") as fp:
                fp.write(themes[color])

    icon_files:List[str] = []
    for icon_template in icon_template_dir.listdir():
        renderer:IconRenderer = IconRenderer(icon_template_dir.join(icon_template))
        colors = [value for color in dark_palette.values() for value in color]
        icons:Dict[str,str] = renderer.render(colors=colors)
        
        for color in icons:
            icon_file:str = f"{File(icon_template).basename()}_{color}.svg"
            icon_files.append(icon_file)
            with icon_dir.join(icon_file).open("w") as fp:
                fp.write(icons[color])

    render_resource_qrc(resource_dir.join("theme.qrc"), template_dir.join("theme.qrc"), theme_files)
    render_resource_qrc(resource_dir.join("icon.qrc"), template_dir.join("icon.qrc"), icon_files)
