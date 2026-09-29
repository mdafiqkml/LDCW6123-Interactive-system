from pathlib import Path
import subprocess,sys,json
root=Path(__file__).resolve().parents[1]
exe=str(root/'wallet.exe')
cases=[
 ('normal_payment','1\n100\n1\n2\n1\n12.50\n1\n4\n6\n',['Transaction #2 | PAYMENT | Campus Cafe | RM12.50','Balance RM87.50']),
 ('insufficient_funds','2\n2\n1\n1\n4\n6\n',['insufficient funds','No successful transactions yet.']),
 ('cancel_topup','1\n100\n2\n3\n4\n6\n',['Cancelled. Balance unchanged.','Available balance: RM0.00','No successful transactions yet.']),
 ('cancel_payment','1\n100\n1\n2\n1\n10\n2\n3\n6\n',['Cancelled. Balance unchanged.','Available balance: RM100.00']),
 ('malformed_input','abc\n1.5\n9\n1\nnan\n-1\n1.001\n12abc\n0\n10\n1\n6\n',['Invalid choice.','Choose a number from 1 to 6.','Invalid amount.','Balance: RM10.00']),
 ('cap','1\n1000\n1\n1\n0.01\n1\n6\n',['simulation balance limit is RM1000.00.']),
 ('cent_precision','1\n0.10\n1\n1\n0.20\n1\n2\n3\n0.30\n1\n3\n6\n',['Transaction #3 | PAYMENT | Campus Mini Mart | RM0.30','Available balance: RM0.00']),
 ('empty_history','4\n6\n',['No successful transactions yet.']),
 ('about','5\n6\n',['not TNG policy','no real money']),
 ('eof_menu','',['No more input.']),
 ('eof_amount','1\n',['No more input.']),
 ('eof_confirmation','1\n10\n',['No more input.']),
 ('whitespace',' 1 \n 10.50 \n1\n6\n',['Balance: RM10.50']),
 ('invalid_merchant','2\n4\n0\n1\n1\n2\n6\n',['Choose a number from 1 to 3.','Cancelled. Balance unchanged.']),
 ('invalid_confirmation','1\n1\n3\na\n2\n6\n',['Choose a number from 1 to 2.','Invalid choice.','Cancelled. Balance unchanged.']),
]
results=[]
for name,data,expected in cases:
 run=subprocess.run([exe],input=data,text=True,capture_output=True,timeout=5)
 assert run.returncode==0,(name,run.stderr)
 assert all(s in run.stdout for s in expected),(name,run.stdout)
 (root/'evidence'/f'{name}.txt').write_text('INPUT\n'+data+'\nACTUAL OUTPUT\n'+run.stdout,encoding='utf-8')
 results.append({'case':name,'result':'PASS'})
print(f'PASS: {len(results)} end-to-end scenarios')
(root/'evidence'/'test_results.json').write_text(json.dumps(results,indent=2))
