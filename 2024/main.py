from dotenv import load_dotenv
from jinja2 import Environment, FileSystemLoader, select_autoescape
import os
from pathlib import Path
import requests
import subprocess
import sys

if __name__=="__main__":
    template_dir ='templates'
    template_loader = FileSystemLoader(searchpath=template_dir)
    template_env = Environment(loader=template_loader,
                               autoescape=True,
                               trim_blocks=True,
                               lstrip_blocks=True,
                               )
    elixir_script_template = template_env.get_template('elixir_template.exs.jinja')
    post_mortem_template = template_env.get_template('post_mortem.md.jinja')
    python_script_template = template_env.get_template('python_template.py.jinja')
    load_dotenv()
    session = os.getenv('AoC_SESSION')

    for day in sys.argv[1:]:
        day_folder = Path(f'day{day}')
        data_folder = Path(day_folder, 'data')
        data_folder.mkdir(parents=True,exist_ok=True)
        elixir_script = Path(day_folder, f'day{day}.exs')
        post_mortem = Path(day_folder, f'README.md')
        python_script = Path(day_folder, f'day{day}.py')
        if not elixir_script.exists():
            with open(elixir_script,'w') as script:
                script.write(elixir_script_template.render(
                    day_number=day,
                ))
        if not post_mortem.exists():
            with open(post_mortem,'w') as script:
                script.write(post_mortem_template.render(
                    day_number=day,
                ))
        if not python_script.exists():
            with open(python_script,'w') as script:
                script.write(python_script_template.render(
                    day_number=day,
                ))
        data_files = [f'input.txt', 'test.txt']
        for f in data_files:
            full_path = Path(data_folder, f)
            if full_path.exists():
                continue
            if 'test' in f: open(full_path, 'w')
            else:
                request = requests.get(f'https://adventofcode.com/2024/day/{day}/input', headers={'Cookie': f'session={session}'})
                if request.status_code == 200:
                    with open(full_path, 'w') as f:
                        f.write(request.content.decode('utf-8'))
                else:
                    print(f'Issue with get request, which returned [{request.status_code}]')
        subprocess.call(['python', python_script])
        subprocess.call(['elixir', elixir_script], shell=True)