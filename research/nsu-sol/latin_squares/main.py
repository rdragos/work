
import requests
from lxml import html

USERNAME = ""
PASSWORD = ""

LOGIN_URL = "http://nsucrypto.nsu.ru/auth/login/"
URL = "http://nsucrypto.nsu.ru/second_round/task3"

def main():
    session_requests = requests.session()

    # Get login csrf token
    result = session_requests.get(LOGIN_URL)
    tree = html.fromstring(result.text)
    authenticity_token = list(set(tree.xpath("//input[@name='csrfmiddlewaretoken']/@value")))[0]

    # Create payload
    payload = {
        "username": USERNAME, 
        "password": PASSWORD, 
        "csrfmiddlewaretoken": authenticity_token
    }

    # Perform login
    result = session_requests.post(LOGIN_URL, data = payload, headers = dict(referer = LOGIN_URL))

    # Scrape url

    payload2 = payload;

    answers = dict()
    f = open("data.txt", "w")
    cnt = 0
    for i in range(10):
        for j in range(10):
            if j == i:
                continue
            for k in range(10):
                if k == j or k == i:
                    continue
                for l in range(10):
                    if l == k or l == j or l == i:
                        continue
                    plain = str(i) + str(j) + str(k) + str(l)
                    payload2['plaintext'] = plain
                    result2 = session_requests.post(URL, data=payload2)
                    tree = html.fromstring(result2.content)
                    qresult = tree.xpath('//td')[3].text
                    answers[plain] = qresult
                    f.write(plain + " " + qresult + "\n")
                    cnt += 1

                    if cnt % 1000 == 0:
                        print "Finished " + str(cnt)
                    #return 0

if __name__ == '__main__':
    main()
