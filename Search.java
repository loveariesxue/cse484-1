import java.io.File;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import org.apache.lucene.document.Document;
import org.apache.lucene.index.DirectoryReader;
import org.apache.lucene.search.IndexSearcher;
import org.apache.lucene.search.Query;
import org.apache.lucene.search.ScoreDoc;
import org.apache.lucene.search.TopDocs;
import org.apache.lucene.search.similarities.DefaultSimilarity;
import org.apache.lucene.search.similarities.Similarity;
import org.apache.lucene.store.FSDirectory;


public class Search {
	private Similarity smfn;
	private IndexSearcher searcher;
	public Search(String indexPath_) throws Exception{
		searcher = new IndexSearcher(DirectoryReader.open(FSDirectory.open(new File(indexPath_))));
		smfn=new DefaultSimilarity()
		{
			public float coord(int q,int d) {
				return 1;
			}
			public float queryNorm(float s) {
				return 1;
			}
			public float tf(float f) {
				return ((float)Math.log(f)+1);
			}
		};
		searcher.setSimilarity(smfn);
	}
	public Map<String,Float> search(Query query) throws IOException{
		Map<String,Float> result=new HashMap<String,Float>();
		TopDocs results=searcher.search(query, 2000);
		ScoreDoc[] hits = results.scoreDocs;
		for (int i=0;i<Math.min(results.totalHits, 1000);i++) {
			Document doc=searcher.doc(hits[i].doc);
			String imgName=doc.get("docno");
			if (result.containsKey(imgName)) {
				if (result.size()>10) {
					break;
				}
				continue;
			}
			result.put(imgName, hits[i].score);
		}
		return result;
	}
}
