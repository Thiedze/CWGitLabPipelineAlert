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

        for index in range(1, 1000):
            response = requests.get(
                self.base_url + '/projects/' + str(project_id) + '/pipelines' + '?per_page=100&page=' + str(index),
                headers=self.headers)
            if len(response.json()) > 0:
                for responsePipeline in response.json():
                    if not any(pipeline['id'] == str(responsePipeline['id']) for pipeline in pipelines):
                        pipelines.append(responsePipeline)
            else:
                break
        return pipelines

    def set_pipeline_status(self):
        # print("set_pipeline_status: start")
        pipelines = self.get_pipelines(self.project_id)
        if len(pipelines) > 0:
            pipeline = pipelines[0]
            self.status = Status[pipeline['status'].upper()]
            # print("set_pipeline_status: " + str(self.status.value))

        # print("set_pipeline_status: end")
