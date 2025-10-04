# 🧮 StarkBTC Flow – CLI Commands List

This document outlines the core, developer, cinematic, and combo commands for running the StarkBTC Flow pipeline. Each command is modular, resilient, and designed for cinematic demo execution.

---

## ⚙️ Core Commands

Basic CLI operations for individual modules.

```bash
./starkbtc --simulate-swap
./starkbtc --verify-wallet
./starkbtc --score
./starkbtc --report-format=md
./starkbtc --report-format=html
./starkbtc --report-format=json
./starkbtc --report-format=all
./starkbtc --open
```

---

## 🛠️ Developer Flags

Advanced flags for debugging, testing, and fee threshold simulation.

```bash
./starkbtc --amount=0.01 --debug --simulate-swap
./starkbtc --amount=0.02 --verify-wallet --report-format=json
./starkbtc --report-format=unknown
```

---

## 🎬 Cinematic Flow

Full pipeline execution with auto-report generation and HTML preview.

```bash
./starkbtc --simulate-swap --verify-wallet --score --report-format=html --open
./starkbtc --simulate-swap --report-format=all --open
```

---

## 🧪 Combo Demos

Multi-flag sequences for Devpost, GitHub, or reviewer walkthroughs.

```bash
./starkbtc --simulate-swap --verify-wallet --score --report-format=all --open
./starkbtc --amount=0.005 --debug --simulate-swap --verify-wallet --report-format=html
```

---




