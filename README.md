# TNG-inspired Campus Wallet Simulator

An offline C++17 classroom simulation of top-ups and merchant payments, connected to the Touch 'n Go eWallet poster using Brian Winston's model.

## Run on Windows
Double-click `RUN_DEMO.bat` or run `wallet.exe` from this folder. The supplied Windows executable is built from these sources. This program uses no real money and requires no account or internet. Each run begins at RM0.00 and loses its history on exit.

## Build from source
With a C++17 compiler available:

```text
g++ -std=c++17 -Wall -Wextra -Wpedantic main.cpp logic.cpp -o wallet.exe
```

Alternatively, with the portable Zig compiler on your PATH:

```text
zig c++ -std=c++17 -Wall -Wextra -Wpedantic main.cpp logic.cpp -o wallet.exe
```

On Linux/macOS, name the output `wallet` and run `./wallet`.

## Demo sequence
1. Top up RM100.00 and confirm. Balance becomes RM100.00.
2. Pay Campus Cafe RM12.50 and confirm. Balance becomes RM87.50.
3. Try paying RM100.00. Payment is rejected and balance stays RM87.50.
4. Enter `abc`, `-1`, `nan`, or `1.001` as an amount. Each is rejected.
5. Enter a valid amount and cancel. Balance stays unchanged.
6. View transaction history and explain successful transaction IDs.
7. Exit. Restart to show the session resets.

## Rules and limitations
- Amounts use integer sen, never floating-point money arithmetic.
- The RM1,000.00 balance cap is a simulation choice, not a statement about actual TNG limits.
- Merchant names are fictional. Choosing a merchant represents only the payment decision after merchant identification; no QR scanning is implemented.
- No banking API, authentication, PIN protection, encryption, real transfers, GO+, or persistent account data is implemented.
- Confirmation reduces accidental input. It is not authentication or fraud protection.

## Test
```text
g++ -std=c++17 -Wall -Wextra -Wpedantic tests/test_wallet.cpp logic.cpp -o wallet_tests.exe
./wallet_tests.exe
python tests/test_cli.py
```
`test_cli.py` expects `wallet.exe` in the project root. Captured inputs and actual outputs are under `evidence/`.

## Development history
```text
git log --oneline --graph --all
git log --format=fuller
```
Keep the hidden `.git` directory when copying the project. The original assignment's `--online` is a typo; the valid flag is `--oneline`.
The two supplied commits are preserved. New commits use the identity **Codex Assistant** and current timestamps. These accurately record this AI-assisted continuation, not historical work or contributions by particular students. The original commits also contain a Claude co-author credit.

## Before submission
Read `../START_HERE.md`. Complete individual declarations truthfully, review the work, record your own group presentation (maximum 18 minutes), and add sharing links. Links are intentionally blank at the group leader's request. Do not claim the project is submitted or lecturer access is verified until those steps are completed.
