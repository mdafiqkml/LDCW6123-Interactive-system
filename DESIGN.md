# Wallet simulation design

Continue the supplied C++ interaction/core separation for Touch 'n Go eWallet.
This is an offline educational simulation, not an official TNG application.

## Inputs and outputs
- Top up: amount in RM, confirm or cancel. Output receipt and updated balance.
- Pay: one of three fictional merchants, amount, confirm or cancel. Output receipt or insufficient funds.
- Balance and session history: no personal data required. Display integer-sen amounts as RM.
- About and Exit: explain connection to cashless payments and end cleanly.

## Rules
Start each run at RM0.00. Store money as integer sen. Accept plain decimal amounts with at most two fractional digits. Reject signs, exponents, non-finite values, trailing text, zero and negative amounts. Simulation balance cap RM1,000.00; not an actual TNG limit. Rejected/cancelled actions leave state unchanged. Successful actions have sequential transaction IDs. No real money, QR scan, network, authentication, transfers, investment or persistent account data.

## Verification plan
Test exact-cent arithmetic, boundaries, insufficient funds, unchanged state after rejection/cancellation, receipts/history, malformed input, repeated operations, EOF, and export/readability of project evidence.

## Provenance
The archive contains two original commits by mohammadHosein, both crediting Claude. Preserve these. Further commits record actual AI-assisted changes made during this continuation, using the assistant identity and current timestamps. They do not establish individual student contributions. Students must review, understand, adapt and accurately disclose assistance under their course rules.
