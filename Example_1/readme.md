# Soufflé Benchmark Analyzer

Dit pakketje leest alle `*.json` profilerbestanden uit `./benchmarks/`, bouwt
nette tabellen, maakt figuren en voert de belangrijkste statistische toetsen uit.

## 1) Virtuele omgeving

```bash
python3 -m venv .venv
# Linux/macOS:
source .venv/bin/activate
# Windows (Powershell):
# .venv\Scripts\Activate.ps1

pip install --upgrade pip
pip install -r requirements.txt


python analyze_benchmarks_json.py   --bench-dir ./benchmarks   --out-dir ./analysis_json   --min-runs 5