' This is a file that makes a yes or no message box

Response = MsgBox("Yes or No?", vbYesNo, "Yes or No?")

if Response = vbYes then
  msgbox("Yes!")
else 
  msgbox("No!")
end if  
  
