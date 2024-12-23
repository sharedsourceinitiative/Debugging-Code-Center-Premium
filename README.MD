<!DOCTYPE html>
<h2>How to: Debug with Code Center Premium Source (Visual Studio 2010)</h2><p>    This article is an extensive update to the MSDN article of the <a href="http://msdn.microsoft.com/en-us/library/ms164729.aspx" target="_blank">same name</a>.
 Thanks to Microsoft C++ MVPs Jim Beveridge and John Czopowik for this 
update. The majority of the content below originally appeared on Jim 
Beveridge’s technical blog.</p><p><i>These instructions are for 
developers who have a Windows Shared Source Initiative source code 
license and access to Code Center Premium.</i></p><h3>To prepare for debugging with Code Center Premium and Visual Studio 2010</h3><ol><li>Close all copies of Visual Studio that are running (this is required or VS will overwrite your registry changes.)</li><li>Connect your smart card reader and insert the card you obtained from the Shared Source Initiative.</li><li>If needed, see <a href="https://www.microsoft.com/en-us/sharedsource/troubleshooting-code-center-premium.aspx">http://www.microsoft.com/en-us/sharedsource/troubleshooting-code-center-premium.aspx</a> for instructions on how to get the latest Gemalto driver for your smart card reader.</li><li>Make sure your smart card certificate is working by opening Internet Explorer and going to <a href="https://codepremium.msdn.microsoft.com/" target="_blank">https://codepremium.msdn.microsoft.com/</a>.
 You should see prompts as shown in Steps 3 to 6 under Sample 
Walkthrough, below. This must work properly before you proceed with 
these instructions. Not all browsers support smart cards, so first try 
this with Internet Explorer.</li><li>Open the Registry Editor and go to:<br><br><b>HKEY_CURRENT_USER\Software\Microsoft\VisualStudio\10.0\Debugger</b></li><li>Set both <i>SecureSourceLocalDirectory</i> and <i>SourceServerExtractToDirectory</i> to the same directory. The directory does not have to already exist.</li><li>Launch Visual Studio.</li><li>On the <b>Tools</b> menu, click <b>Options</b>.</li><li>In the <b>Options</b> dialog box, open the <b>Debugging</b> node and click <b>General</b>.</li><li>Clear the <b>Enable just my code (Managed only)</b> check box.</li><li>Select <b>Enable Enable source server support</b>.</li><li>Select <b>Print source server diagnostic messages to the Output window</b>.</li><li>Clear <b>Require source files to exactly match the original version</b>.</li><li>Under the <b>Debugging</b> node, click <b>Symbols</b>. </li><li>In the <b>Symbol file (.pdb) locations</b> box, clear the <b>Microsoft Server Symbols</b> check box and add the following location:<br><br><b>https://codepremium.msdn.microsoft.com/symbols</b><br><br>Move
 this location to be second in the list to ensure that these symbols are
 loaded first. (You can't move it to the top. Microsoft Symbol Servers 
is always first, but you should have unchecked it.) In the screen shot 
below, note the third entry in this list, C:\Windows\symbols\dll. This 
directory is where the MFC and C run-time symbols are installed by 
Visual Studio. These symbols are not part of Code Center Premium, so you
 need to include them if you want to debug into MFC or the C run-time 
library.<br><br><img src="Shared%20Source%20Initiative%20Debugging_files/debugging_1.png" width="400" height="122" alt="Symbols"><br><br></li><li>In the <b>Cache symbols in this directory</b>
 box, enter a location such as C:\symbols where Code Center Premium can 
cache the symbols. This location should be DIFFERENT from the location 
used to store public symbols when Microsoft Symbol Servers is checked 
because symbols already downloaded from the Microsoft Symbol Servers 
will prevent symbols being downloaded from Code Center Premium.</li><li>Click <b>OK</b>.</li><li>Right-click the Solution under Solution Explorer and choose <b>Properties</b>:<br><br><img src="Shared%20Source%20Initiative%20Debugging_files/debugging_2.png" width="329" height="400" alt="Solution Explorer"><br><br></li><li>Under <b>Common Properties</b>, select <b>Debug Source Files</b>.</li><li>Add a link for the desired operating system (complete list at the end of this article.) For example:<br><br><b>https://codepremium.msdn.microsoft.com/source/Windows%207/RTM</b><br><br>Note that spaces must be replaced with %20, and you cannot browse to this location in your browser.<br><br><img src="Shared%20Source%20Initiative%20Debugging_files/debugging_3.png" width="400" height="78" alt="Debug Source Files"><br><br></li><li>In the same window, make sure that the list under <b>"Do not look for these source files"</b> is empty. </li><li>Click <b>OK</b>. </li><li>Close and restart Visual Studio to ensure that settings are persisted.</li></ol><h3>Sample Code</h3><p>Here is sample code that I used for testing. It's a native code console application that can be tested under x86 or x64:</p><p style="font-family:courier;font-size:12px;">    #include "stdafx.h"<br><br>    #include &lt;windows.h&gt; <br>      #include &lt;shlwapi.h&gt; <br><br>        #pragma comment(lib, "shlwapi.lib")<br><br>        int _tmain(int argc, _TCHAR* argv[])<br>        {<br>        // Can't step into this function. You get a "not indexed" error.<br>        //char buf[256]={'\0'};<br>        //::PathRemoveExtensionA(buf);<br><br>        // Set a breakpoint on this function, then try to Step Into it.<br>        GetConsoleMode(0,0);<br><br>        // Stepping into this function should work too, but not on XP.<br>        //UnregisterApplicationRestart();<br><br>        return 0;<br>        }        </p><h3>Sample Walkthrough</h3><ol><li>Set a breakpoint at <b>GetConsoleMode</b> in the sample code.</li><li>Start debugging (F5).</li><li>You should see the <b>Confirm Certificate</b> window. If not, your smart card isn't working.<br><br><img src="Shared%20Source%20Initiative%20Debugging_files/debugging_4.png" width="320" height="193" alt="Confirm Certificate"><br></li><li>Click <b>OK</b>.</li><li>You'll be asked to enter your PIN. You received this in your email confirmation that welcomed you to Code Center Premium.    <br><br><img src="Shared%20Source%20Initiative%20Debugging_files/debugging_5.png" width="320" height="181" alt="Enter PIN"><br></li><li>Enter your PIN and click <b>OK</b>.</li><li>It
 may take a while to get started because the private symbols must be 
downloaded. Since they contain full debug information, they are much 
larger than the usual symbols.</li><li>When Visual Studio stops at the 
breakpoint, look at your Modules window. Here's how it appears on my 
Windows 7 64-bit machine: (click it to see it full size.)    <br><br><a href="https://www.microsoft.com/global/en-us/sharedsource/PublishingImages/debugging_6_fullsize.png" width="1385" height="127" alt="Modules Window" target="_blank"><img src="Shared%20Source%20Initiative%20Debugging_files/debugging_6.png" width="320" height="20" alt="Modules Window"></a><br></li><li>Note
 that kernel32.dll shows "Symbols loaded", whereas KernelBase.dll shows 
"Symbols loaded (source information stripped). If kernel32.dll also 
shows "(source information stripped)", then you are using the wrong 
symbols. The most likely cause is if you didn't set a different cache 
directory for private symbols.</li><li>Also note that the timestamp for 
both kernel32.dll and KernelBase.dll is 7/13/2009. This means that they 
are RTM DLLs for Windows 7. The timestamp for ntdll.dll is 3/23/2010, 
which means that it's been updated and you can't step into it. So it is <i>possible</i> to debug on a patched system, but it's hit or miss because many DLLs have been patched and so can't be stepped into.</li><li>Now you will see a window asking to execute an untrusted command named SD.EXE:    <br><br><img src="Shared%20Source%20Initiative%20Debugging_files/debugging_7.png" width="320" height="222" alt="Security Warning"><br></li><li>This
 command will be executed by the Source Server at Code Center Premium. 
It will NOT be executed on your computer. You do not need to have SD.EXE
 on your computer.</li><li>Click <b>Run</b>.</li><li>You should now be looking at Windows source code.</li><li>If you look at the Output window, you should see messages such as the following: (some NDA information removed.)<br><br><p style="font-family:courier;font-size:12px;">
    SRCSRV: sd.exe -p windowsdepot.sys-ntgroup.ntdev.microsoft.com:2016 
print -o 
"C:\Users\JimB\AppData\Local\SOURCE~2\WIN_WINDOWS\win7_rtm\windows\yyy\yyy\yyy\yyy.c\1\yyy.c"
 -q //depot/win7_rtm/windows/Core/xxx/xxx/xxxxx.c#1<br><br>    SRCSRV: 
Source server cannot retrieve the source code for file 
'd:\w7rtm\windows\zzz\zzz\zzz\zzz.c' in module 
'C:\Windows\System32\kernel32.dll'. The system cannot find the file 
specified.    </p></li><li>Note that Source Server is actually showing an error. In spite of this, debugging still works properly.</li></ol><h3>Things That Don't Work</h3><ul><li>You
 can't debug into 32-bit code running under a 64-bit operating system. 
In other words, you can't debug into any DLL that lives in 
\Windows\SysWOW64. (Remote debugging into a 32-bit virtual machine 
running under a 64-bit operating system is okay.) </li><li>You can't 
debug any hot fixes, security fixes or operating system updates. You can
 ONLY debug the RTM release or a service pack. In practice, this usually
 means that you are remote debugging a virtual machine that was 
installed from the DVD and Windows Update has been turned off. </li><li>You
 can't debug when running Visual Studio under Remote Desktop because the
 smart card doesn't work when you are logged in under Remote Desktop. 
(LogMeIn and GotoMyPC are not tested.) </li><li>The debugger won't step 
into some Windows functions. This usually means that you are trying to 
step into a DLL that's been updated since the original release. </li><li>Some functions are in files that Code Center Premium can't find. One example is <b>PathRemoveExtensionA</b> in shlwapi.dll. For files that can't be found, you'll see a "not indexed" error in your Output window:    <br><br><p style="font-family:courier;font-size:12px;">    SRCSRV: o:\w7rtm.obj.amd64fre\shell\shlwapi\srca\objfre\amd64\patha.cpp not indexed    </p></li></ul><h3>Troubleshooting</h3><p>Everything has to be exactly right for source code debugging to work properly. If things aren't working, here are some ideas:</p><ul><li>Is your smart card working?  (Repeat Step 4 under <b>Prepare for debugging</b>, above.) </li><li>Did
 Visual Studio overwrite your registry entries? This usually leads to 
the error "SRCSRV: ... The system cannot find the file specified." 
(Repeat Step 5.) </li><li>Did the file get added to the list of <b>Do not look for these source files</b>? (See Steps 18 through 22.) </li><li>Are
 you debugging a 32-bit app on 64-bit Windows? You can't debug Windows 
source in this case. Run the 32-bit code on a 32-bit version of Windows 
in a virtual machine and use Remote Debugging. </li><li>Are you trying 
to step into the Windows kernel? Kernel debugging is different from user
 mode debugging. You must use WinDbg for kernel mode debugging. </li><li>Is
 the source code missing on Code Center Premium? This would be the case 
if you are getting the error SRCSRV: ... not indexed. Please see the 
section below titled <i>ANSI versus Unicode Functions</i>. </li><li>Are you seeing a warning about an "Untrusted Command"? This is normal. Just click <b>Run</b>. </li><li>Can't
 step into a Windows API function? Make sure you have symbols for the 
DLL. Look in the Modules list and make sure that it does NOT say "Source
 information stripped." If it does, clear your symbol cache and run your
 app again.</li></ul><h3>Running Visual Studio in a Virtual Machine</h3><p>You
 can install Visual Studio 2010 on your Windows 7 clean machine and run 
Visual Studio 2010 in the virtual machine so you don't have to use 
remote debugging. However, you must use a virtual machine that supports 
USB devices, such as VMware or Virtual PC in Windows 7. Virtual PC 2007 
will not work (not even with SP1.)</p><p>In Virtual PC on Windows 7, go 
to the USB menu and select USB Smart Card Reader. You will be prompted 
to install the drivers in the virtual machine. The smart card will be 
DISCONNECTED from the host system, so you will not be able to use it in 
the host machine until the virtual machine releases it.</p><p>You do not need to do this if you are using Remote Debugging to run your application in the virtual machine.</p><h3>ANSI versus Unicode Functions</h3><p>Debugging
 into the "A" and "W" versions of functions frequently doesn't work. 
Here is the explanation from C++ MVP Jochen Kalmbach:</p><p>The problem 
with " PathRemoveExtensionA" seems to be a "build feature". They 
implemented the file only once for A and W and then you use this file 
without "A, W"... In this case, the source file is called "path.c" and 
is referenced as "patha.c" (A) and "pathw.c" (W).</p><p>If you want to 
debug into this file, copy the source from the CCP-Website for the 
"TCHAR" version and save it wherever you want with the name "patha.c" 
and/or "pathw.c". Then if VS asks you for the file, you can just use 
this file. It will exactly match.</p><p>It seems that this file is 
generated during the build-process, because it seems that it is also 
compiled from the output directory...</p><h3>Source Server Paths</h3><p>(Thanks again to C++ MVP Jochen Kalmbach for providing this list.)</p><p>Here
 is the list of all currently available source server paths. Links are 
not clickable because these links are only for use in Visual Studio, not
 in your browser.</p><p><b>Win7 RTM</b>: https://codepremium.msdn.microsoft.com/source/Windows%207/RTM </p><p><b>Win7 SP1</b>: https://codepremium.msdn.microsoft.com/source/Windows%207/SP1 </p><p><b>W2k8 RTM</b>: https://codepremium.msdn.microsoft.com/source/Windows%20Server%202008/RTM </p><p><b>W2k8 Hyper-V-RTM</b>: https://codepremium.msdn.microsoft.com/source/Windows%20Server%202008/Hyper-V%20RTM </p><p><b>W2k8 SP2</b>: https://codepremium.msdn.microsoft.com/source/Windows%20Server%202008/SP2 </p><p><b>W2k8 R2</b>: https://codepremium.msdn.microsoft.com/source/Windows%20Server%202008/R2 </p><p><b>W2k3 RTM</b>: https://codepremium.msdn.microsoft.com/source/Windows%20Server%202003/RTM </p><p><b>W2k3 R2</b>: https://codepremium.msdn.microsoft.com/source/Windows%20Server%202003/Windows%20Server%202003%20R2 </p><p><b>W2k3 SP1</b>: https://codepremium.msdn.microsoft.com/source/Windows%20Server%202003/Windows%20Server%202003%20SP1%20RTM </p><p><b>W2k3 SP2</b>: https://codepremium.msdn.microsoft.com/source/Windows%20Server%202003/Windows%20Server%202003%20SP2%20RTM </p><p><b>Vista RTM</b>: https://codepremium.msdn.microsoft.com/source/Windows%20Vista/RTM </p><p><b>Vista SP1</b>: https://codepremium.msdn.microsoft.com/source/Windows%20Vista/SP1 </p><p><b>Vista SP2</b>: https://codepremium.msdn.microsoft.com/source/Windows%20Vista/SP2 </p><p><b>XP RTM</b>: https://codepremium.msdn.microsoft.com/source/windows%20XP/RTM </p><p><b>XP SP1</b>: https://codepremium.msdn.microsoft.com/source/windows%20XP/SP1 </p><p><b>XP SP2</b>: https://codepremium.msdn.microsoft.com/source/windows%20XP/SP2 </p><p><b>XP SP3</b>: https://codepremium.msdn.microsoft.com/source/windows%20XP/SP3 </p><p><b>W2k Datacenter RTM</b>: https://codepremium.msdn.microsoft.com/source/Windows%202000/Datacenter%20RTM </p><p><b>W2k SP3</b>: https://codepremium.msdn.microsoft.com/source/Windows%202000/SP3 </p><p><b>W2k SP4</b>: https://codepremium.msdn.microsoft.com/source/Windows%202000/SP4  </p></div></div></div></body></html>