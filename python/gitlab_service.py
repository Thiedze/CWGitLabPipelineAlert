import requests

from status import Status


class GitLabService:

    def __init__(self, base_url, access_token, project_id):  # access_token = access_token
        self.base_url = 'https://' + base_url + '/api/v4'
        self.headers = {'Authorization': 'Bearer ' + access_token, 'Content-Type': 'application/json'}
        self.status = Status.CREATED
        self.project_id = project_id

    def get_pipelines(self, project_id):
        pipelines = []

        for index in range(1, 2):
            response = requests.get(
                self.base_url + '/projects/' + str(project_id) + '/pipelines' + '?per_page=10&page=' + str(index),
                headers=self.headers)
            if 200 <= response.status_code < 300:
                if len(response.json()) > 0:
                    for responsePipeline in response.json():
                        if not any(pipeline['id'] == str(responsePipeline['id']) for pipeline in pipelines):
                            pipelines.append(responsePipeline)
                else:
                    break
            else:
                print(str(response.status_code))
        return pipelines

    def set_pipeline_status(self):
        try:
            # print("set_pipeline_status: start")
            pipelines = self.get_pipelines(self.project_id)
            if len(pipelines) > 0:
                pipeline = pipelines[0]
                self.status = Status[pipeline['status'].upper()]
                print("set_pipeline_status: " + str(self.status.value))
        except Exception as exception:
            print("set_pipeline_status error: " + str(exception))

        # print("set_pipeline_status: end")
