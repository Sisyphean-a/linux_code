import requests
import re
import os

def getHTML(url,proxise):
    r=requests.get(url,proxies=proxies)
    r.raise_for_status()
    r.encoding=r.apparent_encoding
    return r.text

def findHTMLText(html):
    patt=re.compile(r'\bwatch\?\b.{13}')
    lis=patt.findall(html)
    return lis

def writeText(lis):
    with open('油管爬取.txt','w') as f:
        f.write('')
    for i in lis:
        with open('油管爬取.txt','a') as f:
	        f.write('https://www.youtube.com/'+i+'\n')

if __name__=='__main__':
    url="https://www.youtube.com/channel/UCUrJvRXzVBOYtHBs9fDnJEw/videos"
    proxies={'http':'http://localhost:41091','https':'http://localhost:41091'}
    print('开始收集')
    html=getHTML(url,proxies)
    lis=findHTMLText(html)
    writeText(lis)
    print('收集成功')
