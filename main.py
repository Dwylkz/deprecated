from bs4 import BeautifulSoup
from urllib import request
import urllib
import sys
import json

if __name__ == '__main__':
    proxy = {'http':'127.0.0.1:1080','https':'127.0.0.1:1080'}
    proxies = request.ProxyHandler(proxy)
    opener = request.build_opener(proxies)


    # html = opener.open('https://pornhub.com/video/search?=jav+creampie&page={}'.format(16)).read().decode()
    html = opener.open(sys.argv[1]).read().decode()
    soup = BeautifulSoup(html, features="lxml")
    sectionWrapper = soup.body.select(".wrapper")[0].select(".container")[0].select(".gridWrapper")[0].select(".nf-videos")[0].select(".sectionWrapper")[0]

    opener.addheaders = [ 
            ('Connection', 'keep-alive'),
            ('Pragma', 'no-cache'),
            ('Cache-Control', 'no-cache'),
            ('Upgrade-Insecure-Requests', '1'),
            ('User-Agent', 'Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/81.0.4044.138 Mobile Safari/537.36'),
            ('Accept', 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9'),
            ('Sec-Fetch-Site', 'none'),
            ('Sec-Fetch-Mode', 'navigate'),
            ('Sec-Fetch-User', '?1'),
            ('Sec-Fetch-Dest', 'document'),
            ('Accept-Language', 'en-US,en;q=0.9,zh-CN;q=0.8,zh;q=0.7'),
            ]

    for item in sectionWrapper.select(".videos")[0].select(".pcVideoListItem"):
        raw = 'https://www.pornhub.com{}'.format(item.div.select(".phimage")[0].a["href"])
        # print(raw)
        #params = {'video': raw}
        #downloadpage = 'https://www.tubeoffline.com/downloadFrom.php?host=PornHub&video={}'.format(raw);
        #downloadpage = 'https://www.tubeoffline.com/downloadFrom.php?host=PornHub&{}'.format(urllib.parse.urlencode(params));
        #print(downloadpage)
        downhtml = opener.open(raw).read().decode()
        begin = downhtml.find("mediaDefinitions")
        end = downhtml.find("isVertical")
        # print(begin, end)
        if begin == -1 or end == -1:
            continue
        medias_dict = json.loads(("{"+downhtml[begin-1:end-2]+"}"))
        medias = [x for x in filter(lambda media: media['format']=='mp4', medias_dict["mediaDefinitions"])]
        medias.sort(key=lambda media: int(media['quality']), reverse=True)
        if len(medias) == 0:
            continue
        print(medias[0]["videoUrl"])
